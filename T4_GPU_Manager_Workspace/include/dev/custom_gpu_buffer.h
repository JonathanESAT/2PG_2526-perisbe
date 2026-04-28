/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022.
 *
 * Custom GPU buffer header file.
 *
 * Check the following OpenGL functions:
 *   glBindBuffer
 *   glBufferData
 *   glBufferSubData
 *   glDeleteBuffers
 *   glGenBuffers
 * 
 */
 
#ifndef __CUSTOM_GPU_BUFFER_H__
#define __CUSTOM_GPU_BUFFER_H__ 1

#include "EDK/dev/edk_buffer.h"

typedef unsigned int GLuint;

namespace EDK {

namespace dev {

class CustomGPUBuffer : public EDK::dev::Buffer {
 public:
  CustomGPUBuffer();
  virtual void init(const Buffer::Target t, unsigned int size) override;
  virtual void bind(const Target t) const override;
  virtual void uploadData(const void *data, unsigned int size,
                          unsigned int offset = 0) override;
  virtual void release() override;
  virtual const unsigned int size() const override;


 protected:
  virtual ~CustomGPUBuffer();

  //TODO any data here?
  GLuint id_;
  GLuint size_buffer_;
  GLuint target_;

 private:
  CustomGPUBuffer(const CustomGPUBuffer&);
  CustomGPUBuffer(CustomGPUBuffer&&);
  CustomGPUBuffer& operator=(const CustomGPUBuffer&);

}; //CustomGPUBuffer

} //dev

} //EDK3

#endif //__CUSTOM_GPU_BUFFER_H__
