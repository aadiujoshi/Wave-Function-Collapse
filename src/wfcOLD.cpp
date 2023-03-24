//#include <math.h>
//#include <stdlib.h>
//
//#include "header_paths.h"
//#include wfc_h
//
//namespace gen{
//    
//    wfc::wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed) : 
//        sample_image(sample_image), output_image(output_image), seed(seed){
//        
//        uint rswidth = sample_image.get_width() / 4;
//        uint rsheight = sample_image.get_height() / 4;
//
//        st_length = (rswidth - 2) * (rsheight - 2);
//        sample_tiles = (tile*)malloc(sizeof(tile) * st_length);
//
//        uint st_ind = 0;
//
//        for (size_t x = 1; x < rswidth - 1; x++) {
//            for (size_t y = 1; y < rsheight - 1; y++) {
//
//                uint t_i = x + rswidth * y;
//
//                tile& t = sample_tiles[st_ind];
//                t.t_id = t_i;
//
//                for (int rx = -1; rx <= 1; rx++) {
//                    for (int ry = -1; ry <= 1; ry++) {
//                        uint t_i2 = (x + rx) + rswidth * (y + ry);
//                        t.adj_constraints[(rx + 1) + 3 * (ry + 1)] = t_i2;
//                    }
//                }
//                st_ind++;
//            }
//        }
//
//        srand(seed);
//
//        //init output tiles, and add random tile
//        output_tiles.tiles = (tile*)malloc(sizeof(tile) * (output_image.get_width() / 4) * (output_image.get_height() / 4));
//        output_tiles.tiles[0] = sample_tiles[(int)(rand_f() * st_length)];
//
//    }
//
//    wfc::~wfc() {
//    }
//
//    void wfc::next_collapse(){
//        //FIND LOWEST ENTROPY TILE IN OUTPUT
//        float lowest_entropy = 1;
//        float lowest_entropy_t_id = 0;
//
//        tile** adj_local = (tile**)_alloca(sizeof(tile*) * 9);
//
//        for (size_t x = 0; x < output_tiles.width; x++) {
//            for (size_t y = 0; y < output_tiles.height; y++) {
//
//                tile* tl = tile_image::tile_at(output_tiles, x, y);
//
//                if (tl == nullptr) continue;
//
//                float entropy = tile::calc_entropy(tl, adj_local);
//            }
//        }
//
//        //COLLAPSE CHOSEN TILE AND CONSTRAINT WITH OTHER TILES
//        
//    }
//}