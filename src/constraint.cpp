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
		}

		void sudoku_constraint::propagate(tile_superpositions& tiles) {
			//remove in same row
			for (size_t c = 0; c < tiles.width; c++) {
				tiles[owner->y][c].remove(owner->signature);
			}

			//remove in same col
			for (size_t r = 0; r < tiles.height; r++) {
				tiles[r][owner->x].remove(owner->signature);
			}

			//remove in same squarespace
		}
	}
}