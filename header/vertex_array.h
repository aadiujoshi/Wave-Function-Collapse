#pragma once

#include <vector>
#include "vertex_buffer.h"

namespace graphics {
	class vertex_array {
	private:
		uint id;
	public:
		vertex_array();
		~vertex_array();

		void add_buffer(const vertex_buffer& vb);

		void bind() const;
		void unbind() const;
	};
}