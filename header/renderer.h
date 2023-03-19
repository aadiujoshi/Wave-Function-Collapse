#ifndef RENDERER_GUARD
#define RENDERER_GUARD

#include <string>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"

namespace graphics {
    class renderer {
    private:

    public:
        void clear() const;
        void draw(const graphics::vertex_array& va, const graphics::index_buffer& ib, const graphics::shader& sh) const;
    };
}

#endif