/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022-23
 *
 * Custom terrain implementation.
 *
 */

#include "geometry_custom_terrain.h"
#include "ESAT/math.h"
#include "EDK/dev/edk_gpu_manager.h"

#include <vector>

namespace EDK {

// Un vertice del terreno guarda posicion, normal y coordenada UV.
// En memoria queda: [px,py,pz, nx,ny,nz, u,v] = 8 floats = 32 bytes.
// Esto se llama layout interleaved: todos los datos de un vertice juntos.
struct TerrainVertex {
  esat::Vec3 pos;     // posicion en el espacio 3D
  esat::Vec3 normal;  // direccion perpendicular a la superficie (para luz)
  esat::Vec2 uv;      // coordenada de textura [0..1]
};

// ---------------------------------------------------------------------------
// Constructor / Destructor / Copia
// ---------------------------------------------------------------------------

// El constructor pone todo a cero/false para que el objeto empiece limpio.
TerrainCustom::TerrainCustom()
    : is_initialized_(false), num_rows_(0), num_cols_(0) {}

// El destructor libera los buffers de GPU cuando el objeto se destruye.
TerrainCustom::~TerrainCustom() {
  elements_buffer.release();
  order_buffer.release();
}

// Constructor copia: comparte los mismos buffers de GPU (ref_ptr los cuenta).
TerrainCustom::TerrainCustom(const TerrainCustom& other) {
  elements_buffer  = other.elements_buffer;
  order_buffer     = other.order_buffer;
  is_initialized_  = other.is_initialized_;
  num_rows_        = other.num_rows_;
  num_cols_        = other.num_cols_;
}

// Operador asignacion: igual que el constructor copia pero comprueba
// que no nos estemos asignando a nosotros mismos (this != &other).
TerrainCustom& TerrainCustom::operator=(const TerrainCustom& other) {
  if (this != &other) {
    elements_buffer  = other.elements_buffer;
    order_buffer     = other.order_buffer;
    is_initialized_  = other.is_initialized_;
    num_rows_        = other.num_rows_;
    num_cols_        = other.num_cols_;
  }
  return *this;
}

// ---------------------------------------------------------------------------
// init — genera la geometria del terreno y la sube a la GPU
// ---------------------------------------------------------------------------
//
// El terreno es un grid plano de quads. Cada quad se divide en 2 triangulos:
//
//   tl ---tr      tl = top-left     fila actual,    columna actual
//   | \   |       tr = top-right    fila actual,    columna + 1
//   |  \  |       bl = bottom-left  fila + 1,       columna actual
//   |   \ |       br = bottom-right fila + 1,       columna + 1
//   bl ---br
//
//   Triangulo 1: tl -> bl -> tr
//   Triangulo 2: tr -> bl -> br
//   (orden CCW visto desde arriba = cara visible hacia +Y)

void TerrainCustom::init(const int num_cols, const int num_rows,
                         const float height_mult, const float size,
                         const bool is_centered) {

  // Si ya esta inicializado no hacemos nada (evitar doble init).
  if (is_initialized_) return;
  is_initialized_ = true;

  num_cols_ = num_cols;
  num_rows_ = num_rows;

  // Un grid de NxM quads tiene (N+1)*(M+1) vertices (los puntos de la rejilla).
  const int num_vertices = (num_cols_ + 1) * (num_rows_ + 1);

  // Cada quad = 2 triangulos * 3 indices = 6 indices por quad.
  const int num_indices = num_cols_ * num_rows_ * 6;

  // Reservamos memoria en CPU para rellenar los datos antes de subirlos a GPU.
  std::vector<TerrainVertex> vertices(num_vertices);
  std::vector<unsigned int>  indices(num_indices);

  // Distancia en el mundo entre columna y columna / fila y fila.
  const float col_step = size / static_cast<float>(num_cols_);
  const float row_step = size / static_cast<float>(num_rows_);

  // Si is_centered == true desplazamos el grid para que quede centrado en (0,0).
  // Si is_centered == false el grid empieza en el origen.
  float offset_x = 0.0f;
  float offset_z = 0.0f;
  if (is_centered) {
    offset_x = -size * 0.5f;
    offset_z = -size * 0.5f;
  }

  // --- Generar vertices ---
  // Recorremos fila a fila, columna a columna.
  // El indice lineal de cada vertice es: fila * (num_cols+1) + columna.
  for (int row = 0; row <= num_rows_; ++row) {
    for (int col = 0; col <= num_cols_; ++col) {

      int idx = row * (num_cols_ + 1) + col;

      // Posicion: Y=0 porque el terreno es plano por ahora.
      vertices[idx].pos.x = offset_x + col * col_step;
      vertices[idx].pos.y = 0.0f;
      vertices[idx].pos.z = offset_z + row * row_step;

      // Normal apuntando hacia arriba (eje Y). Todos los vertices igual
      // porque el terreno es un plano horizontal.
      vertices[idx].normal.x = 0.0f;
      vertices[idx].normal.y = 1.0f;
      vertices[idx].normal.z = 0.0f;

      // UV normalizada [0..1]: col/num_cols va de izquierda a derecha,
      // row/num_rows va de arriba a abajo.
      vertices[idx].uv.x = static_cast<float>(col) / static_cast<float>(num_cols_);
      vertices[idx].uv.y = static_cast<float>(row) / static_cast<float>(num_rows_);
    }
  }

  // --- Generar indices ---
  // Para cada quad calculamos los 4 indices de sus esquinas y formamos
  // los 2 triangulos que lo componen.
  int i = 0;
  for (int row = 0; row < num_rows_; ++row) {
    for (int col = 0; col < num_cols_; ++col) {

      unsigned int tl = static_cast<unsigned int>( row      * (num_cols_ + 1) + col    );
      unsigned int tr = static_cast<unsigned int>( row      * (num_cols_ + 1) + col + 1);
      unsigned int bl = static_cast<unsigned int>((row + 1) * (num_cols_ + 1) + col    );
      unsigned int br = static_cast<unsigned int>((row + 1) * (num_cols_ + 1) + col + 1);

      // Triangulo superior-izquierdo
      indices[i++] = tl;
      indices[i++] = bl;
      indices[i++] = tr;

      // Triangulo inferior-derecho
      indices[i++] = tr;
      indices[i++] = bl;
      indices[i++] = br;
    }
  }

  // --- Subir datos a la GPU ---
  // Pedimos al GPUManager que cree dos buffers en GPU:
  //   elements_buffer = VBO, guarda los vertices (posicion, normal, uv).
  //   order_buffer    = EBO, guarda los indices (el orden de dibujo).
  auto& GPU = *EDK::dev::GPUManager::Instance();
  GPU.newBuffer(&elements_buffer);
  GPU.newBuffer(&order_buffer);

  // Tama~no en bytes del VBO: 8 floats por vertice * num_vertices * 4 bytes.
  int vbo_size = 8 * num_vertices * static_cast<int>(sizeof(float));

  // init   = reserva el espacio en GPU con el tipo de buffer correcto.
  // bind   = activa el buffer para que las siguientes operaciones le afecten.
  // upload = copia los datos de RAM a GPU. El ultimo parametro (0) es el offset.
  elements_buffer->init(EDK::dev::Buffer::Target::kTarget_Array_Buffer, vbo_size);
  elements_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
  elements_buffer->uploadData(&vertices[0].pos.x, vbo_size, 0);

  // Tama~no en bytes del EBO: un unsigned int por indice.
  int ebo_size = num_indices * static_cast<int>(sizeof(unsigned int));

  order_buffer->init(dev::Buffer::Target::kTarget_Element_Array_Buffer, ebo_size);
  order_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
  order_buffer->uploadData(indices.data(), ebo_size, 0);

  // height_mult se usara en el futuro para escalar la altura del SimplexNoise.
  // Por ahora lo silenciamos para que el compilador no avise de parametro sin uso.
  (void)height_mult;
}

// ---------------------------------------------------------------------------
// bindAttribute — conecta un atributo semantico al location del shader
// ---------------------------------------------------------------------------
//
// El shader tiene variables de entrada (attributes) en locations 0, 1, 2...
// Esta funcion le dice a la GPU donde dentro del VBO esta cada dato.
//
// enableVertexAttribute recibe:
//   buffer   = de donde leer
//   location = a que variable del shader va
//   type     = tipo de dato (T_FLOAT_3 = vec3, T_FLOAT_2 = vec2)
//   false    = no normalizar los datos
//   offset   = cuantos bytes desde el inicio del vertice hasta este dato
//   stride   = tama~no total de un vertice en bytes (8 floats = 32 bytes)
//
// Layout del vertice en memoria (offsets en bytes):
//   offset  0 -> pos    (3 floats, 12 bytes)
//   offset 12 -> normal (3 floats, 12 bytes)
//   offset 24 -> uv     (2 floats,  8 bytes)

const bool TerrainCustom::bindAttribute(const Attribute a,
                                  unsigned int where_to_bind_attribute) const {
  if (!is_initialized_) return false;

  typedef EDK::dev::GPUManager GPU;

  switch (a) {
    case Attribute::A_POSITION:
      GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
                                             EDK::Type::T_FLOAT_3, false,
                                             0 * sizeof(float),   // offset: empieza al inicio
                                             8 * sizeof(float));  // stride: 8 floats por vertice
      return true;

    case Attribute::A_NORMAL:
      GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
                                             EDK::Type::T_FLOAT_3, false,
                                             3 * sizeof(float),   // offset: despues de pos (3 floats)
                                             8 * sizeof(float));
      return true;

    case Attribute::A_UV:
      GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
                                             EDK::Type::T_FLOAT_2, false,
                                             6 * sizeof(float),   // offset: despues de pos+normal (6 floats)
                                             8 * sizeof(float));
      return true;

    default:
      return false;
  }
}

// ---------------------------------------------------------------------------
// render — lanza la orden de dibujo a la GPU
// ---------------------------------------------------------------------------
//
// drawElements le dice a la GPU:
//   - Dibuja triangulos (kDrawMode_Triangles)
//   - Usando N indices (num_cols * num_rows * 6)
//   - Leyendo los indices del order_buffer
//   - Cada indice es un unsigned int (T_UINT)
//   - Empieza en el offset 0 del buffer

void TerrainCustom::render() const {
  if (!is_initialized_) return;

  typedef EDK::dev::GPUManager GPU;
  GPU::Instance()->drawElements(GPU::DrawMode::kDrawMode_Triangles,
                                num_cols_ * num_rows_ * 6,
                                order_buffer.get(), Type::T_UINT, 0);
}

} // namespace EDK
