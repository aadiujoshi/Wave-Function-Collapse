#include "header_paths.h"
#include renderer_h
#include index_buffer_h
#include "GL/glew.h"

namespace graphics {

	index_buffer::index_buffer(const uint* data, uint count) :
		count(count){
		__ASSERT(sizeof(uint) == sizeof(GLuint));

		glCall(glGenBuffers(1, &id));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
	}

	index_buffer::~index_buffer() {
		glCall(glDeleteBuffers(1, &id));
	}

	void index_buffer::bind() const {
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	}

	void index_buffer::unbind() const {
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}