#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include <string>
#include <vector>
#include <set>
#include "types.h"

typedef struct move {
	char piece_from;
	char piece_to;
	int from;
	int to;
} move_t;

class BoardController {

	const coord_t directions[MAXDIRECTIONS] = {
		{-1, -1}, {-1, 0}, {-1, 1},     ///< UPLEFT, UP, UPRIGHT
		{0, -1}, {0, 1},	  				  ///< LEFT, NOMOVE, RIGHT
		{1, -1}, {1, 0}, {1, 1}, 	  ///< DOWNLEFT, DOWN, DOWNRIGHT

		{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},  ///< KNIGHTS MOVES
		{1, -2},  {2, -1}, {2, 1}, {1, 2}  
	};
	
	std::string board;
	int white_king;
	int black_king;

	std::vector<move_t> game_moves;
	unsigned get_piece_directions(int p);
	int get_piece_steps(int piece);
	bool legal_move(int from, int to);
	bool try_move(int from, int to);
	bool king_checked(int color);
	bool out_of_bounds(coord_t c);

public:
	BoardController();
	void clear_board();
	void set_pieces(std::string b = "");
	
	char get_field(int c);
	int get_color(int c);
	bool same_color(int p1, int p2);
	std::set<int> covered_fields(int color);
	std::vector<move_t> all_moves(int color);
	std::vector<int> piece_moves(int piece);
	int make_move(int from, int to);
	int undo_move();
	void print_board();

	~BoardController(){};
};

#endif


