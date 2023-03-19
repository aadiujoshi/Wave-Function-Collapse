#include <GL/glew.h>	
#include <iostream>

#include "header_paths.h"
#include shader_h
#include renderer_h

namespace graphics {
	uint shader::create_shader(uint shader_type, const std::string& src0) {
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
	uint shader::create_shader_config(const std::string& folder) {
		uint shaderConfig = glCreateProgram();
		uint vs = create_shader(GL_VERTEX_SHADER, gutil::readFile(folder + "/vertex.shader"));
		uint fs = create_shader(GL_FRAGMENT_SHADER, gutil::readFile(folder + "/fragment.shader"));

		glAttachShader(shaderConfig, vs);
		glAttachShader(shaderConfig, fs);
		glLinkProgram(shaderConfig);
		glValidateProgram(shaderConfig);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return shaderConfig;
	}

	shader::shader(const std::string& folder) {
		id = create_shader_config(folder);
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
		uint tloc = 0;

		if (uniform_buffer.find(uniform) == uniform_buffer.end()) {
			glCall(uniform_buffer[uniform] = tloc = glGetUniformLocation(id, uniform.c_str()));
			std::cout << "hashed unif: " << uniform << "  id_loc: " << tloc << std::endl;
		}
		else {
			tloc = uniform_buffer[uniform];
		}

		glCall(glUniform4f(tloc, f1, f2, f3, f4));
	}
}