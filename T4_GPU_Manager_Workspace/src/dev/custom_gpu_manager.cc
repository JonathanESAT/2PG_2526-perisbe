#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_texture.h"

namespace EDK {
	namespace dev {
		void CustomGPUManager::newShader(EDK::ref_ptr<EDK::dev::Shader>* output) {
			if (output) {
				output->allocT<CustomGPUShader>();
			}
		}
		/*
		void newProgram(EDK::ref_ptr<EDK::dev::Program>* output) {

		}
		void newBuffer(EDK::ref_ptr<EDK::dev::Buffer>* output) {

		}
		*/
		void CustomGPUManager::newTexture2D(const Texture::Format internal_format,
			const unsigned int width, const unsigned int height,
			EDK::ref_ptr<Texture>* output) {
			if (output) {
				output->allocT<CustomGPUTexture>()->init(Texture::Type::T_2D, internal_format, width, height, 1);
			}
		}
	}
}