#include "dev/custom_gpu_program.h"
#include "EDK/dev/edk_opengl.h"



namespace EDK {

namespace dev {
    CustomGPUProgram::CustomGPUProgram(){
        //glCreateProgram();
    }
    CustomGPUProgram::~CustomGPUProgram(){
        //glDeleteProgram();
    
    }

    CustomGPUProgram::CustomGPUProgram(const CustomGPUProgram&) {

    }
    CustomGPUProgram& CustomGPUProgram::operator=(const CustomGPUProgram&) {

    }

    void CustomGPUProgram::attach(EDK::dev::Shader* shader) {
        //glAttachShader();
    }
    const bool CustomGPUProgram::link(EDK::scoped_array<char>* link_log) {
        //glLinkProgram();

        //glGetProgramiv();
        //glGetProgramInfoLog();
    }
    void CustomGPUProgram::use() const {
        //glUseProgram();
    }
    const int CustomGPUProgram::get_attrib_location(const char* name) const {
        //glGetAttribLocation();
    }
    const int CustomGPUProgram::get_uniform_position(const char* name) const {
        //glGetUniformLocation();
    }

    //float
    void CustomGPUProgram::set_uniform_value(const int uniform_pos,
        const EDK::Type uniform_type,
        const float* number) const {

    }

    //inteniggers
    void CustomGPUProgram::set_uniform_value(const int uniform_pos,
        const EDK::Type uniform_type,
        const int* number) const {

    }

    //unslave inteniggers
    void CustomGPUProgram::set_uniform_value(const int uniform_pos,
        const EDK::Type uniform_type,
        const unsigned int* number) const {

    }

    const unsigned int CustomGPUProgram::internal_id() const {
        return id_;
    }
}
}