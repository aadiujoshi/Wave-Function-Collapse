#include "header_paths.h"
#include vertex_buffer_h
#include renderer_h
#include "GL/glew.h"

namespace graphics {

	vertex_buffer::vertex_buffer(const void* data, uint size):
		stride(0) {

		glCall(glGenBuffers(1, &id));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, id));
		glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	vertex_buffer::~vertex_buffer() {
		glCall(glDeleteBuffers(1, &id));
	}

	void vertex_buffer::bind() const {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	}

	void vertex_buffer::unbind() const {
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void vertex_buffer::add_layout(const vertex_buffer_layout& vbl){
		vb_layouts.push_back(vbl);
		stride += vbl.count * vertex_buffer_layout::size_of_glType(vbl.type);
	}
}