#include <GL/glew.h>

#include "header_paths.h"
#include renderer_h
#include gutil_h

namespace graphics {

    void renderer::clear() const {
        glCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void renderer::draw(const graphics::vertex_array& va, const graphics::index_buffer& ib, const graphics::shader& sh) const {
        sh.bind();
        va.bind();
        ib.bind();

        glCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
    }
}