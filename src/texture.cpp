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
		for(size_t i = 0; i < tbuffer.size(); i++){
			buffer[i] = tbuffer[i];
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

	texture::texture(const std::string& file) : image(file){
		glCall(glGenTextures(1, &id));
		glCall(glBindTexture(GL_TEXTURE_2D, id));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		uchar* buff = get_buffer();

		//wtf this works so my theory was correct
		// uchar DELTELATER[] = {
		// 	255, 0, 0, 255, 
		// 	0, 255, 0, 255,
		// 	0, 0, 255, 255,
		// 	255, 0, 255, 255,
		// };

		//std::cout << "buffer check: " << (uint)get_buffer()[0] << " " << (uint)get_buffer()[1] << " " << (uint)get_buffer()[2] << " " << std::endl;

		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, get_width(), get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buff));
		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, DELTELATER));
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