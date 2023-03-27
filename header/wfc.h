#pragma once

#include <math.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

#include "texture.h"

#define uchar unsigned char
#define rand_f() (rand()/(float)RAND_MAX)

class wfc::gen::constraint;
class wfc::gen::superposition;
class wfc::gen::tile_superpositions;
class wfc::gen::proximity_constraint;
class wfc::gen::sudoku_constraint;

namespace wfc {

    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;

        gen::tile* sample_tiles;
        uint st_length;

        gen::tile_superpositions& output_tiles;

        const uint seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed);
        ~wfc();

        void next();
    };

    namespace gen {

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        class tile {
        public:
            constraint* constraint;

            float signature;
            bool enabled = true;

            //the original location
            uint sample_x;
            uint sample_y;

            uint x;
            uint y;

            //the original pixel value
            int pixel_val;

            tile(uint sample_x, uint sample_y, int pixel_val);
        };

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        class constraint {
        protected:
            const tile* owner;
        public:
            constraint(std::unordered_map<std::string, void*> varargs);  
            void propagate(tile_superpositions& tiles);
        };

        class proximity_constraint : public constraint {
        private:
            tile* prox;
        public:
            proximity_constraint(std::unordered_map<std::string, void*> varargs);
        };

        class sudoku_constraint : public constraint {
        public:
            sudoku_constraint(std::unordered_map<std::string, void*> varargs);
            void propagate(tile_superpositions& tiles) override;
        };

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================
        
        class superposition {
        private:
            uint count;
        public:
            uint x;
            uint y;

            tile* p_tiles;
            tile* collapsed;

            //SUPPLIED TILES MUST BE OF CONTIGUOUS MEMORY and unique copies of original sample_tiles
            superposition(tile* tiles, uint count, uint x, uint y);
            void remove(uint signature);
            float entropy();
            tile* collapse();
        };

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        class tile_superpositions {
        public:
            superposition* composite;

            uint width;
            uint height;

            tile_superpositions();
            tile_superpositions(tile* sample_tiles, uint sample_width, uint sample_height, uint output_width, uint output_height);
            ~tile_superpositions();

            void remove_at(uint signature, uint x, uint y);

            superposition* operator[](uint col);
            superposition& at(uint index);

        };
    }
}