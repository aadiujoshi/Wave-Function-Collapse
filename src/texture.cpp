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

namespace image {
	class image {
	public:
		std::vector<uchar> buffer;

		uint width, height;

		image(const std::string& file) {
			uint error = lodepng::decode(buffer, width, height, file);

			if (error) {
				std::cerr << "failed to init image : " << file << " : error : " << error << std::endl;
				//exit();
			}
		}

		void bind() {

		}
	};
}