#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include "types.h"

typedef struct move {
	char piece_from;
	char piece_to;
	coord_t from;
	coord_t to;
} move_t;

class ChessController {


coord_t directions[17] = {
	{ -1, -1 }, { -1, 0 }, { -1, 1 },     ///< UPLEFT, UP, UPRIGHT
	{ 0, -1  }, { 0, 0  }, { 0, 1  },	  ///< LEFT, NOMOVE, RIGHT
	{ 1, -1  }, { 1, 0  }, { 1, 1  }, 	  ///< DOWNLEFT, DOWN, DOWNRIGHT

	{ -1, -2 }, { -2, -1 }, { -2, 1}, { -1, 2 },  // KNIGHTS MOVES
	{ 1, -2 }, { 2, -1 }, { 2, 1 }, { 1, 2 } 
};

char board[ROWS][COLUMNS] = {
	{ 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
	{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
	{  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0'  },
	{  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0'  },
	{  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0'  },
	{  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0' ,  '0'  },
	{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
};

std::string black_pieces = "rnbqkp";
std::string white_pieces = "RNBQKP";


	std::vector<move_t> game_moves;
	coord_t make_coord(int r, int c);

public:
	ChessController(){}
	
	int get_color(coord_t c);
	bool same_color(coord_t p1, coord_t p2);
//	std::vector<coord_t> all_moves(int color);
	std::vector<coord_t> piece_moves(coord_t piece, int moves[], int steps);
	void make_move(coord_t from, coord_t to);
	int undo_move();
	void print_board();

	~ChessController(){};
};

#endif


