#include "dev/custom_gpu_shader.h"
#include "EDK/dev/edk_opengl.h"

namespace EDK {

	namespace dev {

		CustomGPUShader::CustomGPUShader() {
			type_ = EDK::dev::Shader::kType_Invalid;
			is_compiled_ = false;
			id_ = 0;
		}

		CustomGPUShader::~CustomGPUShader() {
			if (glIsShader(id_)) {
				glDeleteShader(id_);
			}
		}

		CustomGPUShader::CustomGPUShader(const CustomGPUShader& other) {
			type_ = other.type_;
			is_compiled_ = other.is_compiled_;
			id_ = other.id_;
		}

		CustomGPUShader& CustomGPUShader::operator=(const CustomGPUShader& other) {
			type_ = other.type_;
			is_compiled_ = other.is_compiled_;
			id_ = other.id_;
			return *this;
		}

		CustomGPUShader::CustomGPUShader(CustomGPUShader&& other) {
			type_ = other.type_;
			is_compiled_ = other.is_compiled_;
			id_ = other.id_;
			other.type_ = EDK::dev::Shader::kType_Invalid;
			other.is_compiled_ = false;
			other.id_ = 0;
		}

		const bool CustomGPUShader::compile(EDK::scoped_array<char>* output_log) {
					
			glCompileShader(id_);
			GLint status = GL_FALSE;
			glGetShaderiv(id_, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status) {

				if (output_log) {
					GLint length = 0;
					glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);
					output_log->alloc(length + 1);
					glGetShaderInfoLog(id_, length + 1, &length, output_log->get());
					output_log->get()[length] = '\0';
				}
				is_compiled_ = false;

				return false;
			}
			//compileosen
			if (output_log) {
				output_log->alloc(1);
				output_log->get()[0] = '\0';
			}
			is_compiled_ = true;
			return true;
		}

		void CustomGPUShader::loadSource(const Type shader_type,
			const char* source, const unsigned int source_size) {
			
			if (is_compiled_) return;

			type_ = shader_type;
			switch (type_)
			{
			case EDK::dev::Shader::kType_Vertex:
				id_ = glCreateShader(GL_VERTEX_SHADER);
				break;
			case EDK::dev::Shader::kType_Fragment:
				id_ = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case EDK::dev::Shader::kType_Geometry:
				id_ = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case EDK::dev::Shader::kType_Invalid:
				exit(EXIT_FAILURE);
				break;
			}
			GLint length = 1;
			glShaderSource(id_, 1, &source, &length);
		}


		const EDK::dev::Shader::Type CustomGPUShader::type() const {
			return type_;
		}


		const bool  CustomGPUShader::is_compiled() const {
			return is_compiled_;
		}

		const unsigned int  CustomGPUShader::internal_id() const {
			return id_;
		}
	}
}