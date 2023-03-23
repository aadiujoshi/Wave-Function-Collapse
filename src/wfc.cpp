#include <math.h>
#include <stdlib.h>

#include "header_paths.h"
#include wfc_h

namespace gen{
    
    wfc::wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed) : 
        sample_image(sample_image), output_image(output_image), seed(seed){
        
        uint rswidth = sample_image.get_width() / 4;
        uint rsheight = sample_image.get_height() / 4;

        st_length = (rswidth - 2) * (rsheight - 2);
        sample_tiles = (tile*)malloc(sizeof(tile) * st_length);

        uint st_ind = 0;

        for (size_t x = 1; x < rswidth - 1; x++) {
            for (size_t y = 1; y < rsheight - 1; y++) {

                uint t_i = x + rswidth * y;

                tile& t = sample_tiles[st_ind];
                t.t_id = t_i;

                for (int rx = -1; rx <= 1; rx++) {
                    for (int ry = -1; ry <= 1; ry++) {
                        uint t_i2 = (x + rx) + rswidth * (y + ry);
                        t.adj_constraints[(rx + 1) + 3 * (ry + 1)] = t_i2;
                    }
                }
                st_ind++;
            }
        }

        srand(seed);

        //init output tiles, and add random tile
        output_tiles.tiles = (tile*)malloc(sizeof(tile) * (output_image.get_width()/4) * (output_image.get_height() / 4));
    }

    wfc::~wfc() {
    }

    void wfc::next_collapse(){
        //FIND LOWEST ENTROPY TILE
        //COLLAPSE CHOSEN TILE AND CONSTRAINT WITH OTHER TILES

        float lowest_entropy = 1;
        float lowest_entropy_t_id = 1;
        for (size_t i = 0; i < st_length; i++) {
            
        }
    }
}