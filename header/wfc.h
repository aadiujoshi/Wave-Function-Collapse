#pragma once

#include <math.h>
#include <stdlib.h>
#include <vector>

#include "texture.h"

#define uchar unsigned char
#define rand_f() (rand()/RAND_MAX);

namespace gen {

    //https://www.gridbugs.org/wave-function-collapse/

    typedef struct _tile tile;
    typedef struct _tile {
        //the id of this tile, is also the original index of the sample img
        uint t_id;

        //possible adjacent tile IDs
        uint adj_constraints[9];
        
        static int adj_constraint_at(const tile& tl, int x_rel, int y_rel) {
            return tl.adj_constraints[(1 + x_rel) + 3 * (1 + y_rel)];
        };

        //take the 3x3 adj tile area, 5th index is skipped
        static float calc_entropy(const tile& tl, uint* output_adj) {
            float fit = 0;
            for(int i = 0; i < 9; i++){
                if(i == 4)
                    continue;
                fit += ((output_adj[i] == tl.adj_constraints[i]) ? 1 : 0);
            }

            return (1/fit);
        };

    } tile;
    
    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;

        tile* sample_tiles;
        uint st_length; 

        tile* output_tiles;
        uint ot_length; 

        const uint seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed);
        ~wfc();

        void next_collapse();
    };
}