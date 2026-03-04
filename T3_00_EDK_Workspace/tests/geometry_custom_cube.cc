/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022-23
 *
 * Custom Cube



 source file.
 *
 */

#include "geometry_custom_cube.h"
#include "ESAT/math.h"
#include "EDK/dev/edk_gpu_manager.h"


namespace EDK {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!
    CubeCustom::CubeCustom() : is_initialized_(false) {}

    CubeCustom::~CubeCustom(){
        elements_buffer.release();
        order_buffer.release();
    }
    CubeCustom::CubeCustom(const CubeCustom& other) {
        elements_buffer = other.elements_buffer;
        order_buffer = other.order_buffer;
        is_initialized_ = other.is_initialized_;
    }
    CubeCustom& CubeCustom::operator=(const CubeCustom& other) {
        if (this != &other)
        {
            elements_buffer = other.elements_buffer;
            order_buffer = other.order_buffer;
            is_initialized_ = other.is_initialized_;
        }
        return *this;
    }

    esat::Vec3 Vec3Normalize(const esat::Vec3& v) {
        float h = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        assert(h > 0.0f);
        h /= 1.0f;
        esat::Vec3 tmp = { v.x * h,v.y * h,v.z * h };
        return tmp;
    }

void CubeCustom::init8v(const float Cube_size) {
  //TODO demand graphic resources to the GPUManager.
    if (is_initialized_)return;
    is_initialized_ = true;

    auto& GPU = *EDK::dev::GPUManager::Instance();
    GPU.newBuffer(&elements_buffer);
    GPU.newBuffer(&order_buffer);

  /**
   The Cube face is like this:
         ------------
         |\        |
         | \       |
         |  \      |
         |   \     |
         |    \    |
         |     \   |
         |      \  |
         |       \ |
         |        \|
         ------------
    That's the order of its face.
   */
    float half_size = Cube_size * 0.5f;
  //****** Positions:
    esat::Vec3 positions[8] = {
        {-half_size,   half_size,    half_size},
        {-half_size,  -half_size,    half_size},
        { half_size,  -half_size,    half_size},
        { half_size,   half_size,    half_size},
        {-half_size,   half_size,   -half_size},
        {-half_size,  -half_size,   -half_size},
        { half_size,  -half_size,   -half_size},
        { half_size,   half_size,   -half_size}
    };

  //****** Normals:
    esat::Vec3 normals[8]; 
    for (int i = 0; i < 8; i++)
    {
        normals[i] = Vec3Normalize(positions[i]);
    }

  //****** UVs:
    esat::Vec2 uvs[8] = {
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f }
    };


    struct Vertex {
        esat::Vec3 pos;
        esat::Vec3 normal;
        esat::Vec2 uv;
    };
    Vertex vertices[8];
    for (int i = 0; i < 8; i++)
    {
        vertices[i] = { positions[i], normals[i], uvs[i] };
    }
  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 8 data per element * 2 faces * 
  //               4 vertices per face * sizeof(float)
    int size = 8 * 8 * sizeof(float);
    elements_buffer->init(EDK::dev::Buffer::Target::kTarget_Array_Buffer, size);
    elements_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
    elements_buffer->uploadData(&vertices[0].pos.x, size, 0);
  //36 attributes has a face.


  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
    int elements_order[36] = {  0, 1, 2,  0, 2, 3,   // front
                                7, 6, 5,  7, 5, 4,   // back
                                4, 0, 3,  4, 3, 7,   // top
                                5, 6, 2,  5, 2, 1,   // bottom
                                4, 5, 1,  4, 1, 0,   // left
                                3, 2, 6,  3, 6, 7 }; // right
    order_buffer->init(dev::Buffer::Target::kTarget_Element_Array_Buffer,sizeof(elements_order));
    order_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
    order_buffer->uploadData(elements_order, sizeof(elements_order), 0);
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)
}

void CubeCustom::init24v(const float Cube_size) {
    //TODO demand graphic resources to the GPUManager.
    if (is_initialized_)return;
    is_initialized_ = true;

    auto& GPU = *EDK::dev::GPUManager::Instance();
    GPU.newBuffer(&elements_buffer);
    GPU.newBuffer(&order_buffer);

    /**
     The Cube face is like this:
           ------------
           |\        |
           | \       |
           |  \      |
           |   \     |
           |    \    |
           |     \   |
           |      \  |
           |       \ |
           |        \|
           ------------
      That's the order of its face.
     */
    float half_size = Cube_size * 0.5f;
    //****** Positions: as if you looked each face out of the cube
    esat::Vec3 positions[24] = {
        //front face (mirando desde +Z)
        {-half_size,   half_size,    half_size},  // top-left
        {-half_size,  -half_size,    half_size},  // bottom-left
        { half_size,  -half_size,    half_size},  // bottom-right
        { half_size,   half_size,    half_size},  // top-right

        //back face (mirando desde -Z)
        { half_size,   half_size,   -half_size},  // top-left
        { half_size,  -half_size,   -half_size},  // bottom-left
        {-half_size,  -half_size,   -half_size},  // bottom-right
        {-half_size,   half_size,   -half_size},  // top-right

        //top face (mirando desde +Y)
        {-half_size,   half_size,   -half_size},  // top-left
        {-half_size,   half_size,    half_size},  // bottom-left
        { half_size,   half_size,    half_size},  // bottom-right
        { half_size,   half_size,   -half_size},  // top-right

        //bottom face (mirando desde -Y)
        {-half_size,  -half_size,    half_size},  // top-left
        {-half_size,  -half_size,   -half_size},  // bottom-left
        { half_size,  -half_size,   -half_size},  // bottom-right
        { half_size,  -half_size,    half_size},  // top-right

        //left face (mirando desde -X)
        {-half_size,   half_size,   -half_size},  // top-left
        {-half_size,  -half_size,   -half_size},  // bottom-left
        {-half_size,  -half_size,    half_size},  // bottom-right
        {-half_size,   half_size,    half_size},  // top-right

        //right face (mirando desde +X)
        { half_size,   half_size,    half_size},  // top-left
        { half_size,  -half_size,    half_size},  // bottom-left
        { half_size,  -half_size,   -half_size},  // bottom-right
        { half_size,   half_size,   -half_size},  // top-right
    };

    //****** Normals:
    esat::Vec3 normals[24] = {
        // front (0,0,1)
        {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1},
        // back (0,0,-1)
        {0,0,-1}, {0,0,-1}, {0,0,-1}, {0,0,-1},
        // top (0,1,0)
        {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0},
        // bottom (0,-1,0)
        {0,-1,0}, {0,-1,0}, {0,-1,0}, {0,-1,0},
        // left (-1,0,0)
        {-1,0,0}, {-1,0,0}, {-1,0,0}, {-1,0,0},
        // right (1,0,0)
        {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}
    };
    

    //****** UVs:
    esat::Vec2 uvs[24] = {
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };


    struct Vertex {
        esat::Vec3 pos;
        esat::Vec3 normal;
        esat::Vec2 uv;
    };
    Vertex vertices[24];
    for (int i = 0; i < 24; i++)
    {
        vertices[i] = { positions[i], normals[i], uvs[i] };
    }
    //****** Upload data:
    //TODO initialize and upload data to the "elements_buffer".
    //Size in bytes: 8 data per element * 6 faces * 
    //               4 vertices per face * sizeof(float)
    int size = 8 * 24 * sizeof(float);
    elements_buffer->init(EDK::dev::Buffer::Target::kTarget_Array_Buffer, size);
    elements_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
    elements_buffer->uploadData(&vertices[0].pos.x, size, 0);
    //36 attributes has a face.


    //****** Upload order:
    //TODO initialize and upload data to the "order_buffer".
    int elements_order[36] = {  0,  1,  2,   0,  2,  3,
                                4,  5,  6,   4,  6,  7,
                                8,  9, 10,   8, 10, 11,
                               12, 13, 14,  12, 14, 15,
                               16, 17, 18,  16, 18, 19,
                               20, 21, 22,  20, 22, 23  };
    order_buffer->init(dev::Buffer::Target::kTarget_Element_Array_Buffer, sizeof(elements_order));
    order_buffer->bind(dev::Buffer::kTarget_Element_Array_Buffer);
    order_buffer->uploadData(elements_order, sizeof(elements_order), 0);
    //Remember to order triangles in counter clockwise direction!!
    //6 vertices per face * 1 faces * sizeof(short int)
}

const bool CubeCustom::bindAttribute(const Attribute a,
                     unsigned int where_to_bind_attribute) const {

    typedef EDK::dev::GPUManager GPU;

    switch (a){
    case Attribute::A_POSITION:
        GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
                                                EDK::Type::T_FLOAT_3, false,
                                                0 * sizeof(float),
                                                8 * sizeof(float));
        return true;
        break;
    case Attribute::A_NORMAL:
        GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
            EDK::Type::T_FLOAT_3, false,
            3 * sizeof(float),
            8 * sizeof(float));
        return true;
        break;
    case Attribute::A_UV:
        GPU::Instance()->enableVertexAttribute(elements_buffer.get(), where_to_bind_attribute,
            EDK::Type::T_FLOAT_2, false,
            6 * sizeof(float),
            8 * sizeof(float));
        return true;
        break;
    }
    return false;

  //TODO
  //EDK::dev::GPUManager::Instance()->enableVertexAttribute
}

void CubeCustom::render() const {
  //TODO
  //EDK::dev::GPUManager::Instance()->drawElements
    typedef EDK::dev::GPUManager GPU;
    GPU::Instance()->drawElements(GPU::DrawMode::kDrawMode_Triangles, 36, order_buffer.get(), Type::T_UINT, 0);

}

} //EDK