/**
 *
 * Manu Golpe as 23K elo CS2 player
 *
 * Custom GPU shader header file.
 *
 * Check the following OpenGL functions:
 *   glCompileShader
 *   glDeleteShader
 *   glShaderSource
 *   glGetShaderiv
 *   glGetShaderInfoLog
 *   glCreateShader
 *
 */

#ifndef __CUSTOM_GPU_SHADER_H__
#define __CUSTOM_GPU_SHADER_H__ 1

#include "EDK/dev/edk_shader.h"

typedef unsigned int GLuint;

namespace EDK {

namespace dev {

class CustomGPUShader : public EDK::dev::Shader {
 public:
  CustomGPUShader();

  virtual void loadSource(const Type shader_type, 
                          const char *source,
                          const unsigned int source_size) override;

  virtual const bool compile(EDK::scoped_array<char> *output_log = NULL) override;
  virtual const EDK::dev::Shader::Type type() const override;
  virtual const bool is_compiled() const override;
  virtual const unsigned int internal_id() const override;

 protected:
  virtual ~CustomGPUShader();

  //TODO any data here?
  EDK::dev::Shader::Type type_;
  bool is_compiled_;
  GLuint id_;

 private:
  CustomGPUShader(const CustomGPUShader&);
  CustomGPUShader(CustomGPUShader&&);
  CustomGPUShader& operator=(const CustomGPUShader&);

}; //CustomGPUShader

} //dev

} //EDK

#endif //__CUSTOM_GPU_SHADER_H__
