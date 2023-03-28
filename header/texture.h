#pragma once

#include <string>
#include <lodepng.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>


#define uint unsigned int
#define uchar unsigned char

namespace graphics {

	class image {
	private:
		uchar* buffer;
		uint width, height, bpp;
		std::string filepath;
	public:
		image(const std::string& file);
		image(uint width, uint height);
		~image();

		void print() const;

		int masked_pixel(uint x, uint y) const;
		int masked_pixel(uint ind) const;

		inline uint get_width() const {
			return width;
		};

		inline uint get_height() const {
			return height;
		};

		inline uchar* get_buffer() {
			return buffer;
		}
	};


	class texture : public image {
	private:
		void _init_texture();
		uint id;
	public:
		texture(const std::string& file);
		texture(uint width, uint height);
		~texture();

		void bind(uint slot = 0) const;
		void unbind() const;
	};
}