#include <math.h>
#include <stdlib.h>
#include <vector>

#include "texture.h"

#define uchar unsigned char

namespace wfc{
    typedef struct _tile{
        const uchar* constraint; 

        static uchar* pixel_relative(unsigned int x_rel, unsigned int y_rel){
            return 
        }
    }


    class wfc{
        private:
            graphics::image& sample_image;
            graphics::image& output_image;

            const std::vector<>
        public:
            wfc(const graphics::image& sample_image, graphics::image& output_image);
            ~wfc();

            void reset();
            void generate(long seed);
    }
}