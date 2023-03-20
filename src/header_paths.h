#ifndef HEADER_PATHS_GUARD
#define HEADER_PATHS_GUARD

#define header_path <C:/Users/aadiu/Desktop/Programming Files/Personal Projects/C++ Projects/Wave Function Collapse/header/

#define __conc(a, b) a##b
#define __comp(a, b) __conc(a, b>)

#define renderer_h			__comp(header_path, renderer.h)
#define texture_h			__comp(header_path, texture.h)
#define vertex_buffer_h		__comp(header_path, vertex_buffer.h)
#define index_buffer_h		__comp(header_path, index_buffer.h)
#define vertex_array_h		__comp(header_path, vertex_array.h)
#define shader_h			__comp(header_path, shader.h)
#define gutil_h				__comp(header_path, gutil.h)
#define wfc_h               __comp(header_path, wfc.h)

#endif