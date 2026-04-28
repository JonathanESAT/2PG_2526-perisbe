/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022.
 *
 * Custom GPU Manager header file.
 *
 * Look the name of each function and search for similar OpenGL 
 * functions.
 * 
 */

#ifndef __CUSTOM_GPU_MANAGER_H__
#define __CUSTOM_GPU_MANAGER_H__ 1

#include <stdio.h>
#include "EDK/dev/edk_opengl.h"
#include "EDK/dev/edk_gpu_manager.h"

namespace EDK {

namespace dev {

class CustomGPUManager : public EDK::dev::GPUManager {
 public:

  virtual void newShader(EDK::ref_ptr<EDK::dev::Shader> *output) override;
  //DESCOMENTAR Y HACER PARANOIAS TOPE DE LOKAS
  //virtual void newProgram(EDK::ref_ptr<EDK::dev::Program> *output) override;
  //virtual void newBuffer(EDK::ref_ptr<EDK::dev::Buffer> *output) override;

  /*
  virtual void newTexture1D(const Texture::Format internal_format, 
                            const unsigned int size,  
                            EDK::ref_ptr<Texture>* output) override;
  */
  virtual void newTexture2D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            EDK::ref_ptr<Texture>* output) override;
  /*
  virtual void newTexture3D(const Texture::Format internal_format, 
                            const unsigned int width, const unsigned int height, 
                            const unsigned int depth, 
                            EDK::ref_ptr<Texture>* output) override;
  */

  /*
  virtual void newFramebuffer(EDK::ref_ptr<Framebuffer>* output) override;
  virtual void clearFrameBuffer(const float rgba[4],
                                const unsigned int FrameBufferOrMask =
                                kFrameBufferColor | kFrameBufferDepth) override;
  */
  
  /*
  virtual void enableDepthTest(const CompareFunc f) override;
  virtual void disableDepthTest() override;
  */

  /*
  virtual void enableBlend(BlendParam source, 
                           BlendParam destination, 
                           BlendOp operation, 
                           const float ConstantColor[4]) override;
  void disableBlend();
  */

  /*
  virtual void enableCullFaces(const FaceType f) override;
  virtual void disableCullFaces() override;
  */

  /*
  virtual void enableScissor(int x, int y,
                             unsigned int width,
                             unsigned int height) override;
  virtual void disableScissor() override;
  */

  /*
  virtual void enableVertexAttribute(const EDK::dev::Buffer *buffer,
                                     const unsigned int attribute_index,
                                     const EDK::Type type,
                                     const bool normalized = false,
                                     const unsigned int offset = 0,
                                     const unsigned int stride = 0) override;
  virtual void disableVertexAttribute(const unsigned int attrib_index) override;
  */

  /*
  virtual void drawElements(const DrawMode mode,
                            unsigned int count,
                            const EDK::dev::Buffer *buffer,
                            const EDK::Type element_type = EDK::Type::T_USHORT,
                            const unsigned int offset = 0) const override;
  */

}; //CustomGPUManager

} //dev

} //EDK

#endif //__CUSTOM_GPU_MANAGER__
