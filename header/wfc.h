#pragma once

#include <math.h>
#include <stdlib.h>
#include <vector>

#include "texture.h"

#define uchar unsigned char
#define rand_f() (rand()/RAND_MAX)

namespace wfc {

    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;

        gen::tile* sample_tiles;
        uint st_length;

        gen::tile_superpositions output_tiles;

        const uint seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed);
        ~wfc();

        void next_collapse();
    };

    namespace gen {
        class constraint {
        public:
            virtual void define(tile& owner, );
            virtual void propogate(const tile_superpositions& tiles, uint x, uint y);

            constraint();
        };

        class tile {
        public:
            constraint constraints;

            uint x;
            uint y;

            tile();
        };

        class cell {
        public:
            //SUPPLIED TILES MUST BE OF CONTIGUOUS MEMORY
            tile* p_tiles;
            cell(tile* tiles);
            void remove(tile* tile_address);
        };

        class tile_superpositions {
        public:
            cell* composite;
            tile_superpositions();
            ~tile_superpositions();
        };
    }
}