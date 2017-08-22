#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <string>
#include <vector>
#include "types.h"

typedef struct move {
	char piece_from;
	char piece_to;
	coord_t from;
	coord_t to;
} move_t;

class BoardController {

	const coord_t directions[MAXDIRECTIONS] = {
		{-1, -1}, {-1, 0}, {-1, 1},     ///< UPLEFT, UP, UPRIGHT
		{0, -1}, {0, 1},	  				  ///< LEFT, NOMOVE, RIGHT
		{1, -1}, {1, 0}, {1, 1}, 	  ///< DOWNLEFT, DOWN, DOWNRIGHT

		{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},  ///< KNIGHTS MOVES
		{1, -2},  {2, -1}, {2, 1}, {1, 2}  
	};
	
	char board[ROWS][COLUMNS];
	coord_t white_king;
	coord_t black_king;

	std::vector<move_t> game_moves;
	coord_t make_coord(int r, int c);
	unsigned get_piece_directions(coord_t p);
	int get_piece_steps(coord_t piece);
	bool legal_move(coord_t from, coord_t to);
	bool king_checked(int color);
	bool out_of_bounds(coord_t c);

public:
	BoardController();
	void clear_board();
	void set_pieces(std::string b = "");
	
	char get_field(int c);
	int get_color(coord_t c);
	bool same_color(coord_t p1, coord_t p2);
	std::vector<coord_t> covered_fields(int color);
	std::vector<coord_t> piece_moves(coord_t piece);
	bool make_move(int from, int to);
	int undo_move();
	void print_board();

	~BoardController(){};
};

#endif


