/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022.
 *
 * Custom GPU program header file.
 *
 * Check the following OpenGL functions:
 *   glAttachShader
 *   glDeleteProgram
 *   glLinkProgram
 *   glUseProgram
 *   glGetUniformLocation
 *   glCreateProgram  
 *   glGetProgramiv
 *   glGetProgramInfoLog
 *   glGetAttribLocation
 *   glUniform(1f, 2f, Matrix2fv...)
 *   glBindAttribLocation // optional
 *
 */

#ifndef __CUSTOM_GPU_PROGRAM_H__
#define __CUSTOM_GPU_PROGRAM_H__ 1

#include "EDK/dev/edk_program.h"
#include "EDK/dev/edk_shader.h"

typedef unsigned int GLuint;

namespace EDK {

namespace dev {

class CustomGPUProgram : public EDK::dev::Program {
 public:
  CustomGPUProgram();

  virtual void attach(EDK::dev::Shader* shader) override;
  virtual const bool link(EDK::scoped_array<char>* link_log) override;
  virtual void use() const override;
  virtual const int get_attrib_location(const char* name) const override;
  virtual const int get_uniform_position(const char* name) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK::Type uniform_type,
                                 const float* number) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK::Type uniform_type,
                                 const int* number) const override;
  virtual void set_uniform_value(const int uniform_pos,
                                 const EDK::Type uniform_type,
                                 const unsigned int* number) const;
  virtual const unsigned int internal_id() const override;


 protected:
  virtual ~CustomGPUProgram();

  //TODO any data here?
  GLuint id_;

 private:
  CustomGPUProgram(const CustomGPUProgram&);
  CustomGPUProgram& operator=(const CustomGPUProgram&);

}; //CustomGPUProgram

} //dev

} //EDK

#endif //__CUSTOM_GPU_PROGRAM_H__
