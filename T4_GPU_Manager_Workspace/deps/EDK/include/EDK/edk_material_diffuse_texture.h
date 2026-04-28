/*
 *
 * Copyright 2014 ESAT. All rights reserved.
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>
 * Diffuse texture material class.
 *
 * Engine updated from 2025 forward by:
 *   Ivan Sancho <isancho@esat.es>
 *
 */

#ifndef __EDK_MAT_DIFFUSE_TEXTURE_H__
#define __EDK_MAT_DIFFUSE_TEXTURE_H__

#include <cstring>
#include "edk_ref_ptr.h"
#include "edk_texture.h"
#include "edk_material.h"
#include "edk_material_settings.h"
#include "dev/edk_program.h"


namespace EDK {

class MatDiffuseTexture : public Material {
 public:
  MatDiffuseTexture();
  virtual const bool enable(const MaterialSettings *) const;
  virtual void setupCamera(const float projection[16], 
                           const float view[16]) const;
  virtual void setupModel(const float m[16]) const;

  virtual unsigned int num_attributes_required() const;
  virtual Attribute attribute_at_index(const unsigned int idx) const;
  virtual Type attribute_type_at_index(const unsigned int idx) const;

  class Settings : public MaterialSettings {
   public:
    Settings() { 
      light_color_[0] = 1.0f;
      light_color_[1] = 1.0f;
      light_color_[2] = 1.0f;
      light_color_[3] = 1.0f;
    
      light_dir_[0] = 1.0f;
      light_dir_[1] = 1.0f;
      light_dir_[2] = 1.0f;
    }

    //Light color:
    void set_lightColor(const float r, const float g, const float b, 
                        const float a = 1.0f) {
      light_color_[0] = r;
      light_color_[1] = g; 
      light_color_[2] = b;
      light_color_[3] = a;
    }
    const float *color() const { return light_color_; }

    //Light direction:
    void set_lightDir(const float x, const float y, const float z) {
      light_dir_[0] = 1.0f;
      light_dir_[1] = 1.0f;
      light_dir_[2] = 1.0f;
    }
    const float* lightDir() const { return light_dir_; }

    //Texture:
    void set_texture(Texture *tex) { texture_ = tex; }
    Texture* texture() { return texture_.get(); }
    const Texture* texture() const { return texture_.get(); }

   protected:
    virtual ~Settings() {}
   private:
    Settings(const Settings&);
    Settings& operator=(const Settings&);
    float light_color_[4];
    float light_dir_[3];
    ref_ptr<Texture> texture_;
  }; //Settings

 protected:
  virtual ~MatDiffuseTexture() {}

 private:
  EDK::ref_ptr<dev::Program> program_;
  MatDiffuseTexture(const MatDiffuseTexture&);
  MatDiffuseTexture& operator=(const MatDiffuseTexture &);
}; //MatDiffuseTexture

} //EDK

#endif //__EDK_MAT_DIFFUSE_TEXTURE_H__
