/**
 *
 * Ivan Sancho as Unreal Authorized Instructor (UAI), 2022.
 *
 * Custom GPU texture header file.
 *
 * Check the following OpenGL functions:
 *   glActiveTexture
 *   glBindTexture
 *   glGenerateMipmap
 *   glBindTexture
 *   glPixelStorei(GL_UNPACK_ALIGNMENT, GL_UNPACK_LSB_FIRST)
 *   glGenTextures
 *   glDeleteTextures
 *   glTexImage(1D, 2D, 3D)
 *   glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, 
 *                   GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_R, 
 *                   GL_TEXTURE_WRAP_S)
 *
 */

#ifndef __CUSTOM_GPU_TEXTURE_H__
#define __CUSTOM_GPU_TEXTURE_H__ 1

#include "EDK/edk_ref_ptr.h"
#include "EDK/edk_texture.h"

typedef unsigned int GLuint;

namespace EDK {

class CustomGPUTexture : public EDK::Texture {
 public:
  CustomGPUTexture();

  void init(Type t, Format internal_format, unsigned int width,
            unsigned int height, unsigned int depth);

  virtual void set_data(const Format f, 
                        const EDK::Type t, 
                        const void* data, 
                        unsigned int mipmap_LOD = 0) override;

  virtual void bind(unsigned int textUnit) const override;
  virtual const unsigned int internal_id() const override;

  virtual void set_min_filter(Filter f) override;
  virtual void set_mag_filter(Filter f) override;
  virtual void set_wrap_s(Wrap c) override;
  virtual void set_wrap_t(Wrap c) override;
  virtual void set_wrap_r(Wrap c) override;
  virtual void generateMipmaps() const override;

 protected:
  virtual ~CustomGPUTexture();

  //TODO any data here?
  GLuint id_;

 private:
  CustomGPUTexture(const CustomGPUTexture&);
  CustomGPUTexture& operator=(const CustomGPUTexture&);

  friend class CustomGPUManager;


}; //CustomGPUTexture

} //EDK

#endif //__CUSTOM_GPU_TEXTURE_H__
