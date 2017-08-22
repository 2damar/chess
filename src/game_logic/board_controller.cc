#include <iostream>
#include "board_controller.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

/**
 * Constructor
 * Creates empty board
 */
BoardController::BoardController() 
{
	clear_board();
	set_pieces();
}

/**
 * Clears the board
 */
void BoardController::clear_board()
{
	for(int r = 0; r < ROWS; r++)
		for(int c = 0; c < COLUMNS; c++)
			board[r][c] = EMPTY;
}

/**
 * Initializes the board with the pieces
 * 
 * @param b board fields with pieces
 */
void BoardController::set_pieces(string b)
{
	if(b.empty() || b.size() != 64) {
		for(int c = 0; c < COLUMNS; c++) { //pawns
			board[1][c] = 'p';
			board[6][c] = 'P';
		}

		board[0][0] = board[0][7] = 'r'; // rooks
		board[7][0] = board[7][7] = 'R'; 
		board[0][1] = board[0][6] = 'n'; // knights
		board[7][1] = board[7][6] = 'N';
		board[0][2] = board[0][5] = 'b'; // boardishops
		board[7][2] = board[7][5] = 'B';
		board[0][3] = 'q'; // queens
		board[7][3] = 'Q';
		board[0][4] = 'k'; // kings
		black_king = {0, 4};
		board[7][4] = 'K';
		white_king = {7, 4};
	} else {
		for(int r = 0; r < ROWS; r++)
			for(int c = 0; c < COLUMNS; c++) {
				board[r][c] = b[8*r + c];
				if(board[r][c] == 'k')
					black_king = {r, c};
				else if(board[r][c] == 'K')
					white_king = {r, c};
			}
	}
}
		

/**
 * Returns the piece on the field or EMPTY
 * 
 * @param c index into the board
 * @return piece char or EMPTY
 */
char BoardController::get_field(int c)
{
	return board[c/8][c%8];
}

/**
 * Returns color of the piece
 *
 * @param c location of the piece
 * @return color of the piece, or EMPTY, if the field is empty
 */
int BoardController::get_color(coord_t c)
{
	string black("rnbqkp");
	string white("RNBQKP");
	if(white.find(board[c.row][c.col]) != string::npos)
		return WHITE;
	else if(black.find(board[c.row][c.col]) != string::npos)
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
bool BoardController::same_color(coord_t p1, coord_t p2)
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
unsigned BoardController::get_piece_directions(coord_t c)
{
	switch(board[c.row][c.col]) {
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
int BoardController::get_piece_steps(coord_t c)
{
	char p = board[c.row][c.col];
	// kings and knights
	if(p == 'k' || p == 'K' || p == 'n' || p == 'N')
		return 1;
	
	// pawns 
	if(((p == 'p') && (c.row == 1)) || ((p == 'P') && (c.row == 6)))
		return 2;
	else if((p == 'p') || (p == 'P')) 
		return 1;

	return ROWS;
}

/**
 * Finds out if the king is under attack
 * 
 * @param color color of the king
 * @return true if king is checked, otherwise false
 */
bool BoardController::king_checked(int color)
{
	coord_t king;
	int oponent_color;
	if(color == WHITE) {
		king = white_king;
		oponent_color = BLACK;
	} else {
		king = black_king;
		oponent_color = WHITE;
	}

	vector<coord_t> attack = covered_fields(oponent_color);
	vector<coord_t>::iterator it; 
	for(it = attack.begin(); it != attack.end(); it++) 
		if(((*it).row == king.row) && ((*it).col == king.col))
			break;
	
	if(it != attack.end())
		return true;

	return false;	
}

/**
 * Checks if the coordinates are outside of border
 *
 * @param c coordinates
 * @return true if coordinates are outside of border
 */
bool BoardController::out_of_bounds(coord_t c)
{
	if((c.row < 0) || (c.row >= ROWS) || (c.col < 0) || (c.col >= COLUMNS))
		return true;

	return false;
}

/**
 * Finds all possible moves for a piece
 *
 * @param piece piece's location on the board
 * @param d legal move direction for the piece
 * @param steps legal distance for movement for the piece
 * @return vector of all the possible moves
 * @TODO enpasant, casting
 */
vector<coord_t> BoardController::piece_moves(coord_t piece) 
{
	vector<coord_t> vc;
	unsigned piece_directions = get_piece_directions(piece);
	int steps = get_piece_steps(piece);

	for(int i = 0; i < 16; i++) {
		if((piece_directions & (1 << i)) != 0) {
			
			coord_t c;
			c.row = piece.row + directions[i].row;
			c.col = piece.col + directions[i].col;
			int ex = 1;

			while((!out_of_bounds(c)) && (ex <= steps)) {
				if(board[c.row][c.col] != EMPTY) {
					if(!same_color(piece, c))
						vc.push_back(c);
					break;
				}

				vc.push_back(c);
				++ex;
				c.row = piece.row + ex*directions[i].row;
				c.col = piece.col + ex*directions[i].col;
			}
		}
	}

	// pawn attack
	coord_t pa;
	if(board[piece.row][piece.col] == 'p') {
		pa.row = piece.row + 1;
		pa.col = piece.col - 1;
		if(!out_of_bounds(pa) && !same_color(piece, pa) && board[pa.row][pa.col] != EMPTY) 
			vc.push_back(pa);
		pa.col = piece.col + 1;
		if(!out_of_bounds(pa) && !same_color(piece, pa) && board[pa.row][pa.col] != EMPTY)
			vc.push_back(pa);
	}

	if(board[piece.row][piece.col] == 'P') {
		pa.row = piece.row - 1;
		pa.col = piece.col - 1;
		if(!out_of_bounds(pa) && !same_color(piece, pa) && board[pa.row][pa.col] != EMPTY)
			vc.push_back(pa);
		pa.col = piece.col + 1;
		if(!out_of_bounds(pa) && !same_color(piece, pa) && board[pa.row][pa.col] != EMPTY)
			vc.push_back(pa);
	}

	
	return vc;
}

/**
 * Returns all the field that can player possibly attack
 * 
 * @param color color of the players pieces
 * @return vector of covered fields
 */
vector<coord_t> BoardController::covered_fields(int color)
{
	vector<coord_t> cf;
	vector<coord_t> pm;
	string pieces = (color == WHITE) ? "RNBQKP" : "rnbqkp";
	for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLUMNS; j++) {
			if(pieces.find(board[i][j]) != string::npos) {
				pm = piece_moves(make_coord(i, j));
				for(vector<coord_t>::iterator it = pm.begin(); it != pm.end(); it++)
					cf.push_back(*it);
			}
		}
	
	return cf;
}

/**
 * Checks if the move is possible
 * @param from location of the piece
 * @param to destination where should be piece moved
 * @return true when the move is legal, otherwise false
 */
bool BoardController::legal_move(coord_t from, coord_t to)
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
 * @param from starting position index
 * @param to destination index
 * @return true on successfull move, otherwise false
 */
bool BoardController::make_move(int from, int to)
{	
	coord_t f = make_coord(from/ROWS, from%ROWS);
	coord_t t = make_coord(to/ROWS, to%ROWS);
	if(!legal_move(f, t)) // || king_checked(f, t))
		return false;

	move_t m = { board[f.row][f.col],
					 board[t.row][t.col],
					 f,
					 t };
	
	board[t.row][t.col] = board[f.row][f.col];
	board[f.row][f.col] = EMPTY;
	game_moves.push_back(m);

	if(board[t.row][t.col] == 'k') {
		black_king.row = t.row;
		black_king.col = t.col;
	} else if (board[t.row][t.col] == 'K') {
		white_king.row = t.row;
		white_king.col = t.col;
	}


	int kc = (get_color(t) == WHITE) ? WHITE : BLACK;
	if(king_checked(kc)) {
		undo_move();
		return false;
	}
		
	return true;
}

/**
 * Undoes previous move
 * @return -1 if there is nomore move to undo, otherwise 1
 */
int BoardController::undo_move()
{
	if(game_moves.empty())
		return -1;

	move_t m = game_moves.back();
	board[m.from.row][m.from.col] = m.piece_from;
	board[m.to.row][m.to.col] = m.piece_to;

	if(board[m.from.row][m.from.col] == 'k') {
		black_king.row = m.from.row;
		black_king.col = m.from.col;
	} else if(board[m.from.row][m.from.col] == 'K') {
		white_king.row = m.from.row;
		white_king.col = m.from.col;
	}

	game_moves.pop_back();
	return 1;
}

void BoardController::print_board() 
{
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) 
			cout << "|" << board[i][j];
		cout << "|" << endl;
	}
}

coord_t BoardController::make_coord(int r, int c) 
{
	return {r, c};
}
