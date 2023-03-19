#ifndef INDEX_BUFFER_GUARD
#define INDEX_BUFFER_GUARD

#include "gutil.h"

namespace graphics {
	class index_buffer {
	private:
		uint id;
		uint count;
	public:
		index_buffer(const uint* data, uint count);
		~index_buffer();

		void bind() const;
		void unbind() const;

		inline uint get_count() const { 
			return count; 
		} 
	};
}

#endif