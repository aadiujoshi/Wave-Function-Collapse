#include <math.h>
#include <stdlib.h>
#include <vector>

#include "texture.h"

#define uchar unsigned char

namespace gen {

    //https://www.gridbugs.org/wave-function-collapse/

    typedef struct _tile {
        const uint t_id;
        const uint adj_constraints[9];

        static int adj_constraint_at(const tile& tl, int x_rel, int y_rel) {
            return tl.adj_constraints[(1 + x_rel) + 3 * (1 + y_rel)];
        }

    } tile;


    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;
        const long seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed);
        ~wfc();

        void next_collapse();
    };
}