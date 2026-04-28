#include "dev/custom_gpu_buffer.h"
#include "EDK/dev/edk_opengl.h"


namespace EDK {
namespace dev {

    CustomGPUBuffer::CustomGPUBuffer() {
        id_ = 0;
        size_buffer_ = 0;
        target_ = 0;
        
     }

    CustomGPUBuffer::~CustomGPUBuffer() {
         release();
    }


     void CustomGPUBuffer::init(const Buffer::Target t, unsigned int size) {

         GLenum gl_target;

         if(t == kTarget_Array_Buffer){
            gl_target = GL_ARRAY_BUFFER;
         }else{
            gl_target = GL_ELEMENT_ARRAY_BUFFER;
         }

         target_ = gl_target;

         glGenBuffers(1, &id_);
         glBindBuffer(gl_target, id_);

         glBufferData(gl_target, size, 0, GL_DYNAMIC_DRAW);
         size_buffer_ = size;
     }




     void CustomGPUBuffer::bind(const Target t) const {
         GLenum gl_target;

         if(t == kTarget_Array_Buffer){
            gl_target = GL_ARRAY_BUFFER;
         }else{
            gl_target = GL_ELEMENT_ARRAY_BUFFER;
         }

         glBindBuffer(gl_target, id_);
     }

     
     void CustomGPUBuffer::uploadData(const void* data, unsigned int size,
             unsigned int offset) {
         glBufferSubData(target_, offset, size, data);

     }

     const unsigned int CustomGPUBuffer::size() const {
        return size_buffer_;
     }

     void CustomGPUBuffer::release() {
        if (glIsBuffer(id_))
        {
            glDeleteBuffers(1,&id_);
        }

        id_ = 0;
        size_buffer_ = 0;
        target_ = 0;
        
     }

   
}
}