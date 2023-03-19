#pragma once

#include <string>

#define uint unsigned int
#define uchar unsigned char

#define exit() exit(0xbeef);

#ifdef DEBUG
    #define __ASSERT(x) if(!(x)){__debugbreak();}
#else
    #define __ASSERT(x) if(!(x)){exit();}
#endif

#define glCall(x) gutil::glClearErrors(); x; __ASSERT(gutil::glCheckErrors(#x, __FILE__, __LINE__))

#define UNBIND_ALL() \
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); \
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); \
    glCall(glBindVertexArray(0));

namespace gutil {
    void glClearErrors();
    bool glCheckErrors(const char* func, const char* file, int line);
    std::string readFile(std::string fname);
}