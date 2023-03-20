#pragma once

#include <string>
#include <math.h>
#include <unordered_map>

#define uint unsigned int

namespace graphics {

	class shader {
	private:
		uint _create_shader(uint shader_type, const std::string& src0);
		uint _create_shader_config(const std::string& folder);
		int _uniform_loc(const std::string& uniform);
		uint id;

		std::unordered_map<std::string, int> uniform_buffer;

	public:
		shader(const std::string& src);
		~shader();

		void bind() const;
		void unbind() const;

		void set_4f(const std::string& uniform, float f1, float f2, float f3, float f4);
		void set_1i(const std::string& uniform, int i1);
	};
}