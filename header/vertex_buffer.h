#ifndef VERTEX_BUFFER_GUARD
#define VERTEX_BUFFER_GUARD

#include <vector>
#include <GL/glew.h>
#include "gutil.h"

#define uint unsigned int
#define uchar unsigned char

namespace graphics {
	typedef struct _vertex_buffer_layout {
		uint type;
		uint count;
		uchar normalized;

		static uint size_of_glType(uint glType) {
			switch (glType) {
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
			}
			__ASSERT(false);

			return 0;
		}

	} vertex_buffer_layout;

	class vertex_buffer {
	private:
		std::vector<vertex_buffer_layout> vb_layouts;
		uint id;
		uint stride;
	public:
		vertex_buffer(const void* data, uint size);
		~vertex_buffer();

		void bind() const;
		void unbind() const;

		void add_layout(const vertex_buffer_layout& vbl);

		inline const std::vector<vertex_buffer_layout>& get_layouts() const {
			return vb_layouts;
		};

		inline const uint get_stride() const {
			return stride;
		};
	};
}

#endif