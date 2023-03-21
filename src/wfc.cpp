#include <math.h>
#include <stdlib.h>

#include "header_paths.h"
#include wfc_h

namespace gen{
    
    wfc::wfc(graphics::image& sample_image, graphics::image& output_image, const uint seed) : 
        sample_image(sample_image), output_image(output_image), seed(seed){
        
        srand(seed);
    }

    wfc::~wfc() {
    }

    void wfc::next_collapse(){
        //FIND LOWEST ENTROPY TILE
        //COLLAPSE CHOSEN TILE AND CONSTRAINT WITH OTHER TILES
        //REPEAT (EZ)
    }
}