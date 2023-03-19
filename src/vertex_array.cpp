#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "header_paths.h"
#include vertex_array_h
#include vertex_buffer_h
#include renderer_h

namespace graphics {
	vertex_array::vertex_array() {
		glCall(glGenVertexArrays(1, &id));
		glCall(glBindVertexArray(id));
	}

	vertex_array::~vertex_array() {
		glCall(glDeleteVertexArrays(1, &id));
	}

	void vertex_array::add_buffer(const vertex_buffer& vb) {
		bind();
		vb.bind();

		const std::vector<vertex_buffer_layout> layouts = vb.get_layouts();
		uint layout_offset = 0;

		for(uint i = 0; i < layouts.size(); i++) {
			const vertex_buffer_layout vbl = layouts[i];

			//std::cout << "vbl stuff: " << i << "  " << vbl.count << "  " << vb.get_stride() << "  " << layout_offset << std::endl;

			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, vbl.count, vbl.type, vbl.normalized, 
										8, (const void*)layout_offset));

			layout_offset += vbl.count * vertex_buffer_layout::size_of_glType(vbl.type);
		}
	}

	void vertex_array::bind() const {
		glCall(glBindVertexArray(id));
	}

	void vertex_array::unbind() const {
		glCall(glBindVertexArray(0));
	}
}
