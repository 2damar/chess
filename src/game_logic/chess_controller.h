#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include "types.h"

extern char board[][8];
extern coord_t directions[];

typedef struct move {
	char piece_from;
	char piece_to;
	coord_t from;
	coord_t to;
} move_t;

class ChessController {

	std::string black_pieces = "rnbqkp";
	std::string white_pieces = "RNBQKP";
	coord_t white_king;
	coord_t black_king;

	std::vector<move_t> game_moves;
	coord_t make_coord(int r, int c);
	unsigned get_piece_directions(coord_t p);
	int get_piece_steps(coord_t piece);
	bool legal_move(coord_t from, coord_t to);
	bool king_checked(coord_t from, coord_t to);

public:
	ChessController();
	
	int get_color(coord_t c);
	bool same_color(coord_t p1, coord_t p2);
//	std::vector<coord_t> all_moves(int color);
	std::vector<coord_t> piece_moves(coord_t piece);
	bool make_move(coord_t from, coord_t to);
	int undo_move();
	void print_board();

	~ChessController(){};
};

#endif


