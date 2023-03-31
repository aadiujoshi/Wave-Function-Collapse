#include "header_paths.h"
#include wfc_h

namespace wfc {
	namespace gen {
		constraint::constraint(std::unordered_map<std::string, void*> varargs)
			: owner(static_cast<tile*>(varargs["owner"])) {
		};

		//============================================================================================================
		//============================================================================================================
		//============================================================================================================


		sudoku_constraint::sudoku_constraint(std::unordered_map<std::string, void*> varargs)
			: constraint(varargs){
		};

		void sudoku_constraint::propagate(tile_superpositions* tiles) {
			//remove in same row
			for (size_t c = 0; c < tiles->width; c++) {
				(*tiles)[owner->y][c].remove(owner->signature);
			}

			//remove in same col
			for (size_t r = 0; r < tiles->height; r++) {
				(*tiles)[r][owner->x].remove(owner->signature);
			}

			//remove in same squarespace
		}

		//============================================================================================================
		//============================================================================================================
		//============================================================================================================

		proximity_constraint::proximity_constraint(std::unordered_map<std::string, void*> varargs)
			: constraint(varargs){

			tile* st = static_cast<tile*>(varargs["sample_tiles"]);
			uint stw = *(static_cast<uint*>(varargs["sample_width"]));

			uint i = 0;
			for(int x = -1; x <= 1; x++){
				for(int y = -1; y <= 1; y++){
					prox[i] = st[(owner->x + x) + stw * (owner->y + y)].signature;
					i++;
				}
			}
		};

		void proximity_constraint::propagate(tile_superpositions* tiles) {
			int i = 0;

			tile_superpositions tiles_ = *tiles;

			for(int x = -1 + owner->x; x <= 1; x++){
				for(int y = -1 + owner->y; y <= 1; y++){
					tiles_[y][x].remove_not(prox[i]);
					i++;
				}
			}

		};

		//============================================================================================================
		//============================================================================================================
		//============================================================================================================

		pixel_constraint::pixel_constraint(std::unordered_map<std::string, void*> varargs)
			: constraint(varargs) {
			
			tile* sample_tiles = static_cast<tile*>(varargs["sample_tiles"]);
			uint swidth = *(static_cast<uint*>(varargs["sample_width"]));
			uint sheight = *(static_cast<uint*>(varargs["sample_height"]));
			
			tile ot = *owner;

			int pix_up = sample_tiles[(ot.sample_x) + swidth * (ot.sample_y-1)].pixel_val;
			int pix_down = sample_tiles[(ot.sample_x) + swidth * (ot.sample_y+1)].pixel_val;
			int pix_left = sample_tiles[(ot.sample_x-1) + swidth * (ot.sample_y)].pixel_val;
			int pix_right = sample_tiles[(ot.sample_x+1) + swidth * (ot.sample_y)].pixel_val;


		}
	}
}