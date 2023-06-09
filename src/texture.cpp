#include <string>
#include <lodepng.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "header_paths.h"
#include texture_h
#include gutil_h

#define uint unsigned int
#define uchar unsigned char

namespace graphics {

	image::image(uint width, uint height) : width(width), height(height), bpp(4) {
		buffer = static_cast<uchar*>(operator new[](sizeof(uchar) * width * height * 4));
	}

	image::image(const std::string& file) : buffer(nullptr), width(0), height(0), bpp(4), filepath(file){
		std::vector<uchar> tbuffer;

		uint error = lodepng::decode(tbuffer, width, height, file);

		if (error || tbuffer.data() == nullptr) {
			std::cerr << "failed to init image : " << file << " : error : " << error << std::endl;
			exit();
		}

		std::cout << "successfully loaded png: " << file << ": width: " << width << " : height: " << height << "\n";

		//tbuffer is stack allocated so you cant copy the pointer since it is freed with the stack
		buffer = static_cast<uchar*>(operator new[](sizeof(uchar) * tbuffer.size()));
		
		//copy stack buffer to heap

		size_t sz = tbuffer.size();
		for(size_t i = 0; i < tbuffer.size(); i+=4){
			buffer[i + 0] = tbuffer[sz - i - 1 - 3];
			buffer[i + 1] = tbuffer[sz - i - 1 - 2];
			buffer[i + 2] = tbuffer[sz - i - 1 - 1];
			buffer[i + 3] = tbuffer[sz - i - 1 - 0];
		}
	}

	image::~image() {

	}

	void image::print() const {
		for (size_t i = 0; i < width*height*4; i += 4) {
			std::cout << "at: [" << ((i / 4) % width) << ", " << ((i / 4) / width) << 
				"] : red: " << (uint)buffer[i] <<
				" green: " << (uint)buffer[i + 1] <<
				" blue: " << (uint)buffer[i + 2] << std::endl;
		}
	}

	int image::masked_pixel(uint x, uint y) const {
		return masked_pixel(x + y * width);
	}

	int image::masked_pixel(uint ind) const {
		return  (((int)buffer[ind*4 + 3]) << 24) |
				(((int)buffer[ind*4 + 0]) << 16) |
				(((int)buffer[ind*4 + 1]) << 8) |
				((int)buffer[ind*4 + 2]);
	}

	void texture::_init_texture() {
		glCall(glGenTextures(1, &id));
		glCall(glBindTexture(GL_TEXTURE_2D, id));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		uchar* buff = get_buffer();

		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, get_width(), get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buff));

		glCall(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff));

		set_buffer(buff);

		glCall(glBindTexture(GL_TEXTURE_2D, 0));

	}

	texture::texture(const std::string& file) 
		: image(file) {
		_init_texture();
	}

	texture::texture(uint width, uint height)
		: image(width, height){
		_init_texture();

		for (size_t i = 0; i < width * height; i++) {
			//set_rgba((i % width), (uint)(i / width), 255 * (1.0f * rand() / RAND_MAX), 255 * (1.0f * rand() / RAND_MAX), 255 * (1.0f * rand() / RAND_MAX), 255);
			set_rgba((i % width), (uint)(i / width), 255, 0, 0, 255);
		}
	}

	texture::~texture() {
		image::~image();

		glCall(glDeleteTextures(1, &id));
	}

	void texture::bind(uint slot) const {
		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(GL_TEXTURE_2D, id));
	}
	
	void texture::unbind() const {
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void texture::set_rgba(uint x, uint y, uchar r, uchar g, uchar b, uchar a) {
		uchar* data = (uchar*)_alloca(sizeof(uchar) * 4);

		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;

		bind();
		glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data));
	};
};