#include "header_paths.h"
#include wfc_h
#include texture_h

namespace wfc {

    wfc::wfc(graphics::image& sample_image, graphics::image& output_image, const CONSTRAINT_IMPL impl, const uint seed)
        : sample_image(sample_image), output_image(output_image), seed(seed) {

        uint srwidth = sample_image.get_width();
        uint srheight = sample_image.get_height();

        sample_tiles = static_cast<gen::tile*>(operator new[](sizeof(gen::tile) * srwidth * srheight));
        
        for (size_t i = 0; i < srwidth * srheight; i++) {
            new (sample_tiles + i) gen::tile(i % srwidth, (uint)(i / srwidth), sample_image.masked_pixel(i));
        }

        output_tiles = new gen::tile_superpositions(sample_tiles, impl, srwidth, srheight, output_image.get_width(), output_image.get_height());
    };

    wfc::~wfc() {

    };

    void wfc::next() {
        
        uint lowest_entropy_loc = 0;
        float lowest_entropy = 1;
        //find lowest entropy
        for (size_t i = 0; i < output_tiles->width * output_tiles->height; i++) {
            if (output_tiles->at(i).entropy() < lowest_entropy)
                lowest_entropy = output_tiles->at(i).entropy();
        }

        gen::tile* collapsed_ = output_tiles->composite[lowest_entropy_loc].collapse();
        collapsed_->constraint->propagate(output_tiles);
    }

    namespace gen {

        static uint available_sig = 0;

        tile::tile(uint sample_x, uint sample_y, int pixel_val) 
            :   signature(available_sig++),
                sample_x(sample_x), 
                sample_y(sample_y), 
                pixel_val(pixel_val) {}

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        tile_superpositions::tile_superpositions(int ignore) {};

        tile_superpositions::tile_superpositions(tile* sample_tiles, const CONSTRAINT_IMPL impl, uint sample_width, uint sample_height, uint output_width, uint output_height)
            : width(output_width), height(output_height) {

            composite = static_cast<superposition*>(operator new[](sizeof(superposition) * output_width * output_height));

            uint count = sample_width * sample_height;

            std::unordered_map <std::string, void*> varargs;
            varargs["sample_width"] = (void*)(&sample_width);
            varargs["sample_height"] = (void*)(&sample_height);

            for (size_t i = 0; i < output_width * output_height; i++) {
                tile* u_sample_copy = static_cast<tile*>(operator new[](sizeof(tile) * count));
                memcpy(u_sample_copy, sample_tiles, sizeof(tile) * count);
                new (composite + i) superposition(sample_tiles, count, i % output_width, (uint)(i / output_width));

                tile* pt = composite[i].p_tiles;

                varargs["sample_tiles"] = (void*)(pt);

                for (size_t j = 0; j < count; j++) {
                    switch (impl) {
                        case SUDOKU_CONSTRAINT:{
                            pt[j].constraint = new sudoku_constraint(varargs);
                        }
                        case PROXIMITY_CONSTRAINT: {
                            pt[j].constraint = new proximity_constraint(varargs);
                        }
                    }
                }
            }
        };

        tile_superpositions::~tile_superpositions() {

        };

        void tile_superpositions::remove_at(uint signature, uint x, uint y) {
            this[y][x]->remove(signature); 
        };

        superposition* tile_superpositions::operator[](uint row) {
            return composite + (row * width);
        };

        superposition& tile_superpositions::at(uint index) {
            return composite[index];
        };

        //============================================================================================================
        //============================================================================================================
        //============================================================================================================

        superposition::superposition(tile* sample_tiles, uint count, uint x, uint y) 
            :   p_tiles(sample_tiles), 
                count(count), 
                x(x),
                y(y) {

            for (size_t i = 0; i < count; i++) {
                sample_tiles[i].x = x;
                sample_tiles[i].y = y;
            }
        };

        superposition::~superposition() {
        };

        void superposition::remove(uint signature) {
            for (size_t i = 0; i < count; i++) {
                if (p_tiles[i].signature == signature)
                    p_tiles[i].enabled = false;
            }
        };

        float superposition::entropy() {
            float e = 0;

            for (size_t i = 0; i < count; i++) {
                if (p_tiles[i].enabled)
                    e++;
            }

            return 1/e;
        };

        tile* superposition::collapse() {

            uint ind = (uint)(rand_f() * count);
            while (!(p_tiles[ind = (uint)(rand_f() * count)].enabled));

            collapsed = p_tiles + ind;

            for (size_t i = 0; i < count; i++) {
                if (p_tiles + i != collapsed) {
                    p_tiles[i].enabled = false;
                }
            }

            return collapsed;
        }
    }
}