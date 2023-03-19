#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "header_paths.h"
#include gutil_h

namespace gutil {

    void glClearErrors() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool glCheckErrors(const char* func, const char* file, int line) {

        while (GLenum err = glGetError()) {
            std::cout << "opengl error: " << err << " at : " << func << " line " << line << " in " << file << std::endl;
            return false;
        }

        return true;
    }

    std::string readFile(std::string fname) {
        std::ifstream file(fname);
        if (!file.is_open()) {
            std::cout << "failed to open file" << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}