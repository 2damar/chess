#include <iostream>
#include "chess_controller.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

/**
 * Creates coordinates from row and column
 * @param r row
 * @param c column
 * @return coordinates
 */
coord_t ChessController::make_coord(int r, int c)
{
	coord_t ct = {r, c};
	return ct;
}
 
/**
 * Returns color of the piece
 *
 * @param c location of the piece
 * @return color of the piece, or EMPTY, if the field is empty
 */
int ChessController::get_color(coord_t c)
{
	if(white_pieces.find(board[c.row][c.col]) != string::npos)
		return WHITE;
	else if(black_pieces.find(board[c.row][c.col]) != string::npos)
		return BLACK;
	
	return EMPTY;
}

/**
 * Checks if the two pieces belong to the same player
 *
 * @param p1 first piece
 * @param p2 second piece
 * @return true if pieces have the same color, otherwise false
 */
bool ChessController::same_color(coord_t p1, coord_t p2)
{
	if(get_color(p1) != get_color(p2))
		return false;

	return true;
}

/**
 * Finds all possible move for a piece
 *
 * @param piece piece's location on the board
 * @param d legal move direction for the piece
 * @param steps legal distance for movement for the piece
 * @return vector of all the possible moves
 */
std::vector<coord_t> ChessController::piece_moves(coord_t piece, int d[], int steps) 
{
	std::vector<coord_t> vc;
	for(int i = 1; i < d[0]; i++) {
		int r = piece.row + directions[d[i]].row;
		int c = piece.col + directions[d[i]].col;
		int ex = 1;

		while((r < ROWS) && (r >= 0) && (c < COLUMNS) && (c >= 0) && (ex <= steps)) {
			if(board[r][c] != EMPTY) {
				if(!same_color(piece, make_coord(r, c))) 
					vc.push_back(make_coord(r, c));
				break;
			}
			vc.push_back(make_coord(r, c));
			++ex;
			r = piece.row + ex*directions[d[i]].row;
			c = piece.col + ex*directions[d[i]].col;
		}
	}
	
	return vc;
}

/**
 * Moves the piece and records the move
 *
 * @param from starting position
 * @param to destination
 */
void ChessController::make_move(coord_t from, coord_t to)
{
	move_t m = { board[from.row][from.col],
					 board[to.row][to.col],
					 from,
					 to };
	
	board[to.row][to.col] = board[from.row][from.col];
	board[from.row][from.col] = EMPTY;
	game_moves.push_back(m);
}

/**
 * Undoes previous move
 * @return -1 if there is nomore move to undo, otherwise 1
 */
int ChessController::undo_move()
{
	if(game_moves.empty())
		return -1;

	move_t m = game_moves.back();
	board[m.from.row][m.from.col] = m.piece_from;
	board[m.to.row][m.to.col] = m.piece_to;

	game_moves.pop_back();
	return 1;
}

void ChessController::print_board() 
{
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) 
			cout << "|" << board[i][j];
		cout << "|" << endl;
	}
}
