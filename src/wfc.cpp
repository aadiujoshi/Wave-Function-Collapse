#include <math.h>
#include <stdlib.h>

#include "header_paths.h"
#include wfc_h

namespace gen{
    
    wfc::wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed) : 
        sample_image(sample_image), output_image(output_image), seed(seed){

        sample_tiles.height = sample_image.get_height()/4;
        sample_tiles.width = sample_image.get_width()/4;

        output_tiles.height = output_image.get_height()/4;
        output_tiles.width = output_image.get_width()/4;

        sample_tiles.tiles = (tile*)malloc(sizeof(tile) * (sample_tiles.width-2) * (sample_tiles.height-2));
        output_tiles.tiles = (tile*)malloc(sizeof(tile) * (output_tiles.width-2) * (output_tiles.height-2));

        tile* s_tiles = sample_tiles.tiles;

        //init sample_tiles

        //rel arith
        // translate to 1D: (x + 1) + width * (y + 1) (rel)
        // subtract x and y by 1 to get sample_tiles index

        for (size_t x = 1; x < sample_image.get_width() - 1; x++) {
            for (size_t y = 1; y < sample_image.get_height() - 1; y++) {

                uint t_i = samp_img_to_samp_tile_ind(x, y, sample_tiles.width);

                tile& t = s_tiles[t_i];
                t.t_id = t_i;

                for (int rx = -1; rx <= 1; rx++) {
                    for (int ry = -1; ry <= 1; ry++) {
                        t.adj_constraints[(rx + 1) + 3 * (ry + 1)] = 1;
                    }
                }
            }
        }

        srand(seed);
    }

    wfc::~wfc() {
    }

    void wfc::next_collapse(){

        //FIND LOWEST ENTROPY TILE
        //COLLAPSE CHOSEN TILE AND CONSTRAINT WITH OTHER TILES
        
        
    }
}