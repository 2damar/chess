#include "types.h"

coord_t directions[17] = {
	-9, -8, -7,     ///< UPLEFT, UP, UPRIGHT
	-1,  1,	  				  ///< LEFT, NOMOVE, RIGHT
	 7,  8,  9, 	  ///< DOWNLEFT, DOWN, DOWNRIGHT

	-10, -17, -15, -6,  ///< KNIGHTS MOVES
	  6,  15,  17, 10  
};

char board[ROWS*COLUMNS] = {
	 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
	 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
	 '0', '0', '0', '0', '0', '0', '0', '0',
	 '0', '0', '0', '0', '0', '0', '0', '0',
	 '0', '0', '0', '0', '0', '0', '0', '0',
	 '0', '0', '0', '0', '0', '0', '0', '0',
	 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
};
