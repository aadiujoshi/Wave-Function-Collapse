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

	image::image(const std::string& file) : buffer(nullptr), width(0), height(0), bpp(0), filepath(file){
		std::vector<uchar> tbuffer;

		uint error = lodepng::decode(tbuffer, width, height, file);

		if (error || tbuffer.data() == nullptr) {
			std::cerr << "failed to init image : " << file << " : error : " << error << std::endl;
			exit();
		}

		std::cout << "successfully loaded png: " << file << ": width: " << width << " : height: " << height << "\n";

		//tbuffer is stack allocated so you cant copy the pointer since it is freed with the stack
		buffer = (uchar*)malloc(sizeof(uchar) * tbuffer.size());
		
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
		for (size_t i = 0; i < width*height*16; i += 4) {
			std::cout << "at: [" << ((i / 4) % width) << ", " << ((i / 4) / width) << 
				"] : red: " << (uint)buffer[i] <<
				" green: " << (uint)buffer[i + 1] <<
				" blue: " << (uint)buffer[i + 2] << std::endl;
		}
	}

	int image::masked_pixel(uint x, uint y) const {
		return masked_pixel(x + y * width);
	}

	int image::masked_pixel(uint ind){
		return  (((int)buffer[ind + 3]) << 24) |
				(((int)buffer[ind + 0]) << 16) |
				(((int)buffer[ind + 1]) << 8) |
				((int)buffer[ind + 2]);
	}

	texture::texture(const std::string& file) : image(file){
		glCall(glGenTextures(1, &id));
		glCall(glBindTexture(GL_TEXTURE_2D, id));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		uchar* buff = get_buffer();

		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, get_width(), get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buff));
		glCall(glBindTexture(GL_TEXTURE_2D, 0));

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

}