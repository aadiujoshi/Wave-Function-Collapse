#pragma once

#include <math.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

#include "texture.h"

#define uchar unsigned char
#define rand_f() (rand()/(float)RAND_MAX)

#define CONSTRAINT_IMPL int
#define PROXIMITY_CONSTRAINT 0
#define SUDOKU_CONSTRAINT 1

namespace wfc {

    namespace gen {
        class constraint;
        class superposition;
        class tile_superpositions;

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        class tile {
        public:
            constraint* constraint;

            uint signature;
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
            tile* owner;
        public:
            constraint(std::unordered_map<std::string, void*> varargs);  
            virtual void propagate(tile_superpositions* tiles) = 0;
        };

        class proximity_constraint : public constraint {
        private:
            uint prox[9];
        public:
            proximity_constraint(std::unordered_map<std::string, void*> varargs);
            void propagate(tile_superpositions* tiles) override;
        };

        class sudoku_constraint : public constraint {
        public:
            sudoku_constraint(std::unordered_map<std::string, void*> varargs);
            void propagate(tile_superpositions* tiles) override;
        };

        class pixel_constraint: public constraint {
        private:
            uint* p_up;
            uint* p_down;
            uint* p_left;
            uint* p_right;
        public:
            pixel_constraint(std::unordered_map<std::string, void*> varargs);
            void propagate(tile_superpositions* tiles) override;
        }

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
            ~superposition();
            void remove(uint signature);
            void remove_not(uint signature);
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

            tile_superpositions(int ignore);
            tile_superpositions(tile* sample_tiles, const CONSTRAINT_IMPL impl, uint sample_width, uint sample_height, uint output_width, uint output_height);
            ~tile_superpositions();

            void remove_at(uint signature, uint x, uint y);

            superposition* operator[](uint col);
            superposition& at(uint index);

        };
    }

    class wfc {
    private:
        graphics::image& sample_image;
        graphics::image& output_image;

        gen::tile* sample_tiles;

        gen::tile_superpositions* output_tiles;

        const uint seed;
    public:
        wfc(graphics::image& sample_image, graphics::image& output_image, const CONSTRAINT_IMPL impl, const uint seed);
        ~wfc();

        void next();
    };

}