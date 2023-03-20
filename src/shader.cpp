#include <GL/glew.h>	
#include <iostream>

#include "header_paths.h"
#include shader_h
#include renderer_h

#include <iostream>

namespace graphics {
	uint shader::_create_shader(uint shader_type, const std::string& src0) {
		uint sId = glCreateShader(shader_type);
		const char* src = &src0[0];

		glShaderSource(sId, 1, &src, nullptr);
		glCompileShader(sId);

		int res;
		glGetShaderiv(sId, GL_COMPILE_STATUS, &res);
		if (res == GL_FALSE) {
			int length;
			glGetShaderiv(sId, GL_INFO_LOG_LENGTH, &length);
			char* err = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(sId, length, &length, err);
			std::cout << "Failed to compiler shader: " << shader_type << " : " << err << std::endl;

			glDeleteShader(sId);

			return 0;
		}

		return sId;
	}
	uint shader::_create_shader_config(const std::string& folder) {
		uint shaderConfig = glCreateProgram();
		uint vs = _create_shader(GL_VERTEX_SHADER, gutil::readFile(folder + "/vertex.shader"));
		uint fs = _create_shader(GL_FRAGMENT_SHADER, gutil::readFile(folder + "/fragment.shader"));

		glCall(glAttachShader(shaderConfig, vs));
		glCall(glAttachShader(shaderConfig, fs));
		glCall(glLinkProgram(shaderConfig));
		glCall(glValidateProgram(shaderConfig));

		glCall(glDeleteShader(vs));
		glCall(glDeleteShader(fs));

		return shaderConfig;
	}

	int shader::_uniform_loc(const std::string& uniform) {
		int tloc = 0;

		if (uniform_buffer.find(uniform) == uniform_buffer.end()) {
			glCall(uniform_buffer[uniform] = tloc = glGetUniformLocation(id, uniform.c_str()));

			if (tloc < 0) {
				std::cerr << "could not find uniform: " << uniform << std::endl;
				__ASSERT(false);
			}

			std::cout << "hashed unif: " << uniform << "  id_loc: " << tloc << std::endl;
		}
		else {
			std::cout << "retrieve unif: " << uniform << "  id_loc: " << tloc << std::endl;
			tloc = uniform_buffer[uniform];
		}

		return tloc;
	}

	shader::shader(const std::string& folder) {
		id = _create_shader_config(folder);
		bind();
	}

	shader::~shader() {
		glCall(glDeleteProgram(id));
	}

	void shader::bind() const {
		glCall(glUseProgram(id));
	}

	void shader::unbind() const {
		glCall(glUseProgram(0));
	}

	void shader::set_4f(const std::string& uniform, float f1, float f2, float f3, float f4) {
		glCall(glUniform4f(_uniform_loc(uniform), f1, f2, f3, f4));
	}

	void shader::set_1i(const std::string& uniform, int i1) {
		glCall(glUniform1i(_uniform_loc(uniform), i1));
	}
}