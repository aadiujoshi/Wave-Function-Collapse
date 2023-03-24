#pragma once

#include <math.h>
#include <stdlib.h>
#include <vector>

#include "texture.h"

#define uchar unsigned char
#define rand_f() (rand()/RAND_MAX)

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

        static uint get_samp_tile_index(const tile& tl) {
            return tl.adj_constraints[0];
        };

        //take the 3x3 adj tile area, 5th index is skipped
        static float calc_entropy(const tile& tl, tile** output_adj) {
            float fit = 0;
            for (int i = 0; i < 9; i++) {
                if (i == 4 || output_adj[i] == nullptr)
                    continue;
                fit += (((*output_adj[i]).t_id == tl.adj_constraints[i]) ? 1 : 0);
            }

            return (1 / fit);
        };

    } tile, *tilep;
    
    typedef struct _tile_image tile_image;
    typedef struct _tile_image {
        tile* tiles;
        uint width;
        uint height;

        //adj is tile* array of 9, elements are pointers to adj tiles (non contiguous)
        static void get_adj(const tile_image& ti, const tile** adj, uint x, uint y) {

            int i = 0;

            for (int rx = -1; rx <= 1; rx++) {
                for (int ry = -1; ry <= 1; ry++) {
                    adj[i] = tile_at(ti, x + rx, y + ry);
                    i++;
                }
            }
        }

        static tile* tile_at(const tile_image& ti, uint x, uint y) {
            if (x < 0 || y < 0) {
                std::cout << "returned nullptr for AIOOB index access: " << x << " " << y << std::endl;
                return nullptr;
            }

            return &(ti.tiles[x + y * ti.width]);
        }
    };

    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;

        tile* sample_tiles;
        uint st_length; 

        tile_image output_tiles;

        const uint seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed);
        ~wfc();

        void next_collapse();
    };
}