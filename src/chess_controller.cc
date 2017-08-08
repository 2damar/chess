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
 * Returns all legal directions in which piece can move
 * 
 * @param location of the piece
 * @return flags with possible directions
 */
unsigned ChessController::get_piece_directions(coord_t p)
{
	switch(board[p.row][p.col]) {
		case 'k':
		case 'K': return KINGDIRECTIONS;
		case 'q':
		case 'Q': return QUEENDIRECTIONS;
		case 'r':
		case 'R': return ROOKDIRECTIONS;
		case 'n':
		case 'N': return KNIGHTDIRESTIONS;
		case 'b':
		case 'B': return BISHOPDIRECTIONS;
		case 'p': return BLACKPAWNDIRECTIONS;
		case 'P': return WHITEPAWNDIRECTIONS;
		default : break;
	}

	return 0;
}

/**
 * Returns the possible distance in which piece can move
 *
 * @param p location of the piece
 * @return distance
 */
int ChessController::get_piece_steps(coord_t piece)
{
	char p = board[piece.row][piece.col];
	// kings and knights
	if(p == 'k' || p == 'K' || p == 'n' || p == 'N')
		return 1;
	
	// pawns 
	if(((p == 'p') && (piece.row == 1)) || ((p == 'P') && (piece.row == 6)))
		return 2;
	else 
		return 1;

	return ROWS;
}

/**
 * Finds all possible move for a piece
 *
 * @param piece piece's location on the board
 * @param d legal move direction for the piece
 * @param steps legal distance for movement for the piece
 * @return vector of all the possible moves
 */
vector<coord_t> ChessController::piece_moves(coord_t piece) 
{
	vector<coord_t> vc;
	unsigned piece_directions = get_piece_directions(piece);
	int steps = get_piece_steps(piece);

	for(int i = 0; i < 16; i++) {
		if((piece_directions & (1 << i)) != 0) {
			
			int r = piece.row + directions[i].row;
			int c = piece.col + directions[i].col;
			int ex = 1;

			while((r < ROWS) && (r >= 0) && (c < COLUMNS) && (c >= 0) && (ex <= steps)) {
				if(board[r][c] != EMPTY) {
					if(!same_color(piece, make_coord(r, c))) 
						vc.push_back(make_coord(r, c));
					break;
				}
				vc.push_back(make_coord(r, c));
				++ex;
				r = piece.row + ex*directions[i].row;
				c = piece.col + ex*directions[i].col;
			}
		}
	}
	
	return vc;
}
/**
 * Checks if the move is possible
 * @param from location of the piece
 * @param to destination where should be piece moved
 * @return true when the move is legal, otherwise false
 */
bool ChessController::legal_move(coord_t from, coord_t to)
{
	vector<coord_t> moves = piece_moves(from);
	vector<coord_t>::iterator it;
	for(it = moves.begin(); it != moves.end(); it++)
	{
		if(((*it).row == to.row) && ((*it).col == to.col))
			break;
	}

	if(it != moves.end())
		return true;
	
	return false;
}

/**
 * Moves the piece and records the move
 *
 * @param from starting position
 * @param to destination
 * @return true on successfull move, otherwise false
 */
bool ChessController::make_move(coord_t from, coord_t to)
{	
	if(!legal_move(from, to))
		return false;

	move_t m = { board[from.row][from.col],
					 board[to.row][to.col],
					 from,
					 to };
	
	board[to.row][to.col] = board[from.row][from.col];
	board[from.row][from.col] = EMPTY;
	game_moves.push_back(m);
	return true;
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
