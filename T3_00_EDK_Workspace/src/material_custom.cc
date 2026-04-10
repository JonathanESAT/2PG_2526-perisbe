/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022-23
 *
 * Basic material source file.
 *
 */


#include "material_custom.h"
#include "EDK/dev/edk_shader.h"
#include "EDK/dev/edk_gpu_manager.h"


namespace EDK {


//IMPORTANT!!!
//Type the constructors, destructor and operator= here, just in this point!!!
//If you don't do it, it won't compile!!!
MaterialCustom::MaterialCustom() {}
MaterialCustom::~MaterialCustom() {}
MaterialCustom::MaterialCustom(const MaterialCustom& other) { program_ = other.program_;}
MaterialCustom& MaterialCustom::operator=(const MaterialCustom& other) {
	program_ = other.program_;
	return *this;
}

void MaterialCustom::init(const char* vertex, const char* fragment) {
  //1: Request at least two shaders and one program to the GPU Manager.
	EDK::ref_ptr<EDK::dev::Shader> v_shader;
	EDK::ref_ptr<EDK::dev::Shader> f_shader;
	EDK::dev::GPUManager::Instance()->newShader(&v_shader);
	EDK::dev::GPUManager::Instance()->newShader(&f_shader);
	EDK::dev::GPUManager::Instance()->newProgram(&program_);
    //2: Load the source code to the requested shaders.
    EDK::scoped_array<char> v_src;
    FILE* v_file = fopen(vertex, "rb");
    fseek(v_file, 0, SEEK_END);
    long v_size = ftell(v_file);
    fseek(v_file, 0, SEEK_SET);
    v_src.alloc(v_size + 1);
    fread(v_src.get(), 1, v_size, v_file);
    v_src[v_size] = '\0';
    fclose(v_file);
    v_shader->loadSource(EDK::dev::Shader::Type::kType_Vertex, v_src.get(), v_size);

    EDK::scoped_array<char> f_src;
    FILE* f_file = fopen(fragment, "rb");
    fseek(f_file, 0, SEEK_END);
    long f_size = ftell(f_file);
    fseek(f_file, 0, SEEK_SET);
    f_src.alloc(f_size + 1);
    fread(f_src.get(), 1, f_size, f_file);
    f_src[f_size] = '\0';
    fclose(f_file);
    f_shader->loadSource(EDK::dev::Shader::Type::kType_Fragment, f_src.get(), f_size);
  //3: Compile both shaders.
	EDK::scoped_array<char> log;
	if (false == v_shader->compile(&log)) {
		printf("[Vertex Error]: %s\n", log.get());
	}
	if (false == f_shader->compile(&log)) {
		printf("[Fragment Error]: %s\n", log.get());
	}
  //4: Attach shaders to the program.
	program_->attach(v_shader.get());
	program_->attach(f_shader.get());
  //5: Finally... link the program!
	if (false == program_->link(&log)) {
		printf("[Program Error]: %s\n", log.get());
	}
}

 const bool MaterialCustom::enable(const EDK::MaterialSettings *mat) const {
	 program_->use();
	 typedef MaterialCustomSettings MBS;
	 const MBS* ms = dynamic_cast<const MBS*>(mat); //dynamic convierte en tiempo de ejecucion
	 if (ms) {
		 int loc = program_->get_uniform_position("u_color");
		 program_->set_uniform_value(loc, EDK::Type::T_FLOAT_4, ms->color());
		 return true;
	 }
  //Enable the material...
  //... and use the uniforms located in the material settings!
  return false;
}

void MaterialCustom::setupCamera(const float projection[16],
                                const float view[16]) const {
  //Set the projection and view matrices as uniforms here!
  esat::Mat4 v = esat::Mat4FromColumns(view);
  esat::Mat4 p = esat::Mat4FromColumns(projection);
  esat::Mat4 vp = esat::Mat4Multiply(p, v);
  int loc = program_->get_uniform_position("u_vp_matrix");
  program_->set_uniform_value(loc, EDK::Type::T_MAT_4x4, vp.d);
}

void MaterialCustom::setupModel(const float model[16]) const {
  //Set the model matrix as uniform here!
  int loc = program_->get_uniform_position("u_m_matrix");
  program_->set_uniform_value(loc, EDK::Type::T_MAT_4x4, model);
}

unsigned int MaterialCustom::num_attributes_required() const {
  //Depending on how attributes the geometry has.
  return 3;
}

EDK::Attribute MaterialCustom::attribute_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK::Attribute" enum.
  //Depending on how attributes are stored in the geometry buffer.
  switch(attrib_idx) {
	case 0: return EDK::Attribute::A_POSITION; break;
	case 1: return EDK::Attribute::A_NORMAL; break;
	case 2: return EDK::Attribute::A_UV; break;
  }
	return EDK::Attribute::A_POSITION;
}

EDK::Type MaterialCustom::attribute_type_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK::Type" enum.
  //Depending on how attributes are stored in the geometry buffer.
  switch(attrib_idx) {
	case 0: return EDK::Type::T_FLOAT_3; break;
	case 1: return EDK::Type::T_FLOAT_3; break;
	case 2: return EDK::Type::T_FLOAT_3; break;
  }
	return EDK::Type::T_FLOAT_3;  
}

} //EDK



