#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <set>

#include "types.h"

typedef struct move {
	char piece_from;
	char piece_to;
	int from;
	int to;
} move_t;

class Board {
	
public:
	Board();
	void clear_board();
	void set_pieces(std::string b = "");
	char get_field(int c);
	int get_color(int c);
	std::set<int> covered_fields(int color);
	std::vector<move_t> all_moves(int color);
	std::vector<int> piece_moves(int piece);
	int make_move(int from, int to);
	bool king_checked(int color);
	std::string get_board();

	~Board(){};

private:

	std::string board;
	int white_king;
	int black_king;
	int enpassant;
	int white_0_0;
	int white_0_0_0;
	int black_0_0;
	int black_0_0_0;

//	std::vector<move_t> game_moves;
	std::vector<int> pawn_moves(int position);
	std::vector<int> rook_moves(int position);
	std::vector<int> knight_moves(int position);
	std::vector<int> bishop_moves(int position);
	std::vector<int> queen_moves(int position);
	std::vector<int> king_moves(int position);
	bool same_color(int p1, int p2);
	bool legal_move(int from, int to);
	bool is_king(char piece);
	bool is_pawn(char piece);
	bool try_king_castling(int position);
	bool try_queen_castling(int position);
	bool try_enpassant(int position);
	int try_move(int from, int to);
};

#endif


