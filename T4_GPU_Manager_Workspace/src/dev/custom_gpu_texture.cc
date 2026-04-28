#include "dev/custom_gpu_texture.h"

namespace EDK {

    CustomGPUTexture::CustomGPUTexture(){}

    void CustomGPUTexture::init(Type t, Format internal_format, unsigned int width,
        unsigned int height, unsigned int depth){
        init(...);
    }

    void CustomGPUTexture::set_data(const Format f,
        const EDK::Type t,
        const void* data,
        unsigned int mipmap_LOD = 0){
        //glGenTexture
        //glTexImage(1d,2d,3d)
        //glPixelStorei(GL_UNPACK_ALIGNMENT, GL_UNPACK_LSB_FIRST)

        //MIN_FILTER, MAG_FILTER, WRAP X3, MIPMAPS
    }

    void CustomGPUTexture::bind(unsigned int textUnit) const {
        //glBindTexture
        //glActiveTexture
    }
    const unsigned int CustomGPUTexture::internal_id() const {

    }

    void CustomGPUTexture::set_min_filter(Filter f){
        //glBindTexture
        //glTexParametri --> GL__TEXTURE_MIN_FILTER
    }
    void CustomGPUTexture::set_mag_filter(Filter f){
        //glBindTexture
        //glTexParametri --> GL__TEXTURE_MIN_FILTER
    }
    void CustomGPUTexture::set_wrap_s(Wrap c){
        //glBindTexture
        //glTexParametri --> GL__TEXTURE_WRAP_S        
    }
    void CustomGPUTexture::set_wrap_t(Wrap c){
        //glBindTexture
        //glTexParametri --> GL__TEXTURE_WRAP_T        
        
    }
    void CustomGPUTexture::set_wrap_r(Wrap c){
        //glBindTexture
        //glTexParametri --> GL__TEXTURE_WRAP_C 
        
    }
    void CustomGPUTexture::generateMipmaps() const{
            
    }

    CustomGPUTexture::~CustomGPUTexture(){

    }
    CustomGPUTexture::CustomGPUTexture(const CustomGPUTexture&){

    }
    CustomGPUTexture& CustomGPUTexture::operator=(const CustomGPUTexture&){

    }
}