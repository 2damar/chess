#include <iostream>

#include "board.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::set;

/**
 * Constructor
 * Creates empty board
 */
Board::Board() 
{
	clear_board();
}

/**
 * Clears the board
 */
void Board::clear_board()
{
	board.assign(64, '0');
}

/**
 * Returns the current board
 */
string Board::get_board()
{
	return board;
}

/**
 * Return current board + castling flags + en passant field
 */
board_features_t Board::get_board_features()
{
	return {board, castling_flags, enpassant, WHITE};
}

/**
 * Initializes the board with the pieces, and sets proper flags 
 * 
 * @param b board fields with pieces
 * @param cf castling flags
 * @param ep en passant
 */
void Board::set_pieces(string b, unsigned cf, int ep)
{
	if(b.size() != 64) 
		board = "rnbqkbnrpppppppp00000000000000000000000000000000PPPPPPPPRNBQKBNR";
	else 
		board = b;
	
	castling_flags = cf;
	enpassant = ep;

	white_king = board.find('K');
	black_king = board.find('k');
}
		
/**
 * Returns the piece on the field or EMPTY
 * 
 * @param c index into the board
 * @return piece char or EMPTY
 */
char Board::get_field(int c)
{
	return board[c];
}

/**
 * Returns color of the piece
 *
 * @param c location of the piece
 * @return color of the piece, or EMPTY, if the field is empty
 */
int Board::get_color(int c)
{
	string black("rnbqkp");
	string white("RNBQKP");
	if(white.find(board[c]) != string::npos)
		return WHITE;
	else if(black.find(board[c]) != string::npos)
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
bool Board::same_color(int p1, int p2)
{
	if(get_color(p1) != get_color(p2))
		return false;

	return true;
}

/**
 * Finds out if the king is under attack
 * 
 * @param color color of the king
 * @return true if king is checked, otherwise false
 */
bool Board::king_checked(int color)
{
	int king;
	int oponent_color;
	if(color == WHITE) {
		king = white_king;
		oponent_color = BLACK;
	} else {
		king = black_king;
		oponent_color = WHITE;
	}

	set<int> attack = covered_fields(oponent_color);
	set<int>::iterator it = attack.find(king); 
	if(it != attack.end())
		return true;

	return false;	
}

/**
 * Finds all possible moves for a piece
 *
 * @param piece piece's location on the board
 * @param d legal move direction for the piece
 * @param steps legal distance for movement for the piece
 * @return all the possible moves for the piece
 */
vector<int> Board::piece_moves(int position)
{
	switch(board[position]) {
		case 'p':
		case 'P': return pawn_moves(position);
		case 'r':
		case 'R': return rook_moves(position);
		case 'n':
		case 'N': return knight_moves(position);
		case 'b':
		case 'B': return bishop_moves(position);
		case 'k':
		case 'K': return king_moves(position);
		case 'q':
		case 'Q': return queen_moves(position);
		default : 
				vector<int> empty;
				return empty;
	}
}
	
/**
 * Returns all the field that can player possibly attack
 * 
 * @param color color of the players pieces
 * @return vector of covered fields
 */
set<int> Board::covered_fields(int color)
{
	set<int> cf;
	vector<int> pm;
	string pieces = (color == WHITE) ? "RNBQKP" : "rnbqkp";
	for(int i = 0; i < ROWS*COLUMNS; i++)
		if(pieces.find(board[i]) != string::npos) {
			pm = piece_moves(i);
			for(vector<int>::iterator it = pm.begin(); it != pm.end(); it++)
					cf.insert(*it);
			
		}
	
	return cf;
}

/**
 * Calculates all the possible moves for the player
 *
 * @param color color of the players pieces
 * @return all possible moves
 */
vector<move_t> Board::all_moves(int color)
{
	vector<move_t> am;
	vector<int> pm;
	string pieces = (color == WHITE) ? "RNBQKP" : "rnbqkp";
	for(int i = 0; i < ROWS * COLUMNS; i++) {
		if(pieces.find(board[i]) != string::npos) {
			pm = piece_moves(i);
			for(vector<int>::iterator it = pm.begin(); it != pm.end(); it++) {
				if(try_move(i, *it)) 
					am.push_back({i, *it});
			}
		}
	}

	return am;
}


bool Board::try_king_castling(int position)
{
	string board_castling = board;
	int* king = (position = white_king) ? &white_king : &black_king;
	// part move (move king just by one to the right
	board[position + RIGHT] = board[position];
	board[position] = EMPTY;
	*king = position + RIGHT;
	if(king_checked(get_color(*king))) {
		// king checked during the move
		board = board_castling;
		return false;
	}

	// complete the move (move king one more field to the right + move the rook)
	board[position + 2*RIGHT] = board[position + RIGHT]; // move king by one(in total two)
	board[position + RIGHT] = board[position + 3*RIGHT]; // move rook 'over' the king
	board[position + 3*RIGHT] = EMPTY; // clear the field of the rook
	*king = position + 2*RIGHT;
	if(king_checked(get_color(*king))) {
		board = board_castling;
		return false;
	}
	
	board = board_castling;
	return true;
}

bool Board::try_queen_castling(int position)
{
	string board_castling = board;
	int* king = (position == white_king) ? &white_king : &black_king;
	// part move (move king just by one to the left
	board[position + LEFT] = board[position];
	board[position] = EMPTY;
	*king = position + LEFT;
	if(king_checked(get_color(*king))) {
		// king checked during the move
		board = board_castling;
		return false;
	}

	// complete the move (move king one more field to the left + move the rook)
	board[position + 2*LEFT] = board[position + LEFT]; // move king by one(in total two)
	board[position + LEFT] = board[position + 4*LEFT]; // move rook 'over' the king
	board[position + 4*LEFT] = EMPTY; // clear the rook field
	*king = position + 2*LEFT;
	if(king_checked(get_color(*king))) {
		board = board_castling;
		return false;
	}

	board = board_castling;
	return true;
}

bool Board::try_enpassant(int position)
{
	string board_ep = board;
	int backward = (position < enpassant) ? UP : DOWN;
	board[enpassant] = board[position]; // move pawn
	board[position] = EMPTY; // clear starting position
	board[enpassant + backward] = EMPTY; // take oponnents pawn(which is 'under')
	
	if(king_checked(get_color(enpassant))) {
		board = board_ep;
		return false;
	}

	board = board_ep;
	return true;
}

/** 
 * Checks if the piece is a king
 *
 * @param piece
 * @return true if it is a king, otherwise false
 */
bool Board::is_king(char piece)
{
	return ((piece == 'k') || (piece == 'K'));
}

/**
 * Checks if the piece is a pawn
 *
 * @param piece
 * @return true if it is a pawn, otherwise false
 */
bool Board::is_pawn(char piece)
{
	return ((piece == 'p') || (piece == 'P'));
}
	

/**
 * Simulates the move and finds out if it is possible to make it
 * 
 * @param from starting position
 * @param to destination
 * @return type of move
 */
int Board::try_move(int from, int to)
{
	if(!legal_move(from, to))
		return ILLEGALMOVE;

	string board_move = board;
		
	// king castling 
	if(is_king(board[from]) && (to == from + 2*RIGHT)) { 
		if(try_king_castling(from))
			return KINGCASTLING;
		return ILLEGALMOVE;
	}

	// queen castling
	if(is_king(board[from]) && (to == from + 2*LEFT)) { 
		if(try_queen_castling(from)) 
			return QUEENCASTLING;
		return ILLEGALMOVE;
	}
	
	// en passant
	if(is_pawn(board[from])) {
		if(to == enpassant) {
			if(try_enpassant(from))
				return ENPASSANT;
			else 
				return ILLEGALMOVE;
		}

	}

	// regular move
	int kc = (get_color(from) == WHITE) ? WHITE : BLACK;
	board[to] = board[from]; // move the piece 
	board[from] = EMPTY; // clear the starting position
	if(board[to] == 'k') // check if the king moved and update kings positions info
		black_king = to;
	else if(board[to] == 'K')
		white_king = to;
	
	bool result = king_checked(kc);
	board = board_move;
	if(board[from] == 'k')
		black_king = from;
	else if(board[from] == 'K')
		white_king = from;

	if(result)  // king is checked
		return ILLEGALMOVE;
	
	if(is_pawn(board[from])) { // pawn forward by to, for setting enpassant
		if((from == to + 2*UP) || (from == to + 2*DOWN))
			return PAWNTWOFORWARD;
	}

	return REGULARMOVE;
}


	
	
/**
 * Checks if the move is possible
 * @param from location of the piece
 * @param to destination where should be piece moved
 * @return true when the move is legal, otherwise false
 */
bool Board::legal_move(int from, int to)
{
	vector<int> moves = piece_moves(from);
	vector<int>::iterator it;
	for(it = moves.begin(); it != moves.end(); it++)
	{
		if(*it == to)
			break;
	}

	if(it != moves.end())
		return true;

	return false;
}

/**
 * Moves the piece and records the move
 *
 * @param f starting position index
 * @param t destination index
 * @return true on successfull move, otherwise false
 */
int Board::make_move(int from, int to)
{
	int mv = try_move(from, to);
	string board_before = board;
	
	// execute the move
	switch(mv) {
		case KINGCASTLING:
			board[from + 2*RIGHT] = board[from];
			board[from] = EMPTY;
			board[from + RIGHT] = board[from + 3*RIGHT];
			board[from + 3*RIGHT] = EMPTY;
			enpassant = -1;
			break;

		case QUEENCASTLING:
			board[from + 2*LEFT] = board[from];
			board[from] = EMPTY;
			board[from + LEFT] = board[from + 4*LEFT];
			board[from + 4*LEFT] = EMPTY;
			enpassant = -1;
			break;

		case ENPASSANT:
			board[to] = board[from];
			board[from] = EMPTY; 
			if(from < to)
				board[enpassant + UP] = EMPTY;
			else 
				board[enpassant + DOWN] = EMPTY;
			enpassant = -1;
			break;

		case PAWNTWOFORWARD:
			board[to] = board[from];
			board[from] = EMPTY;
			if(from < to) 
				enpassant = from + DOWN;
			else
				enpassant = from + UP;
			break;

		case REGULARMOVE: 
			board[to] = board[from];
			board[from] = EMPTY;
			enpassant = -1;		
			break;

		case ILLEGALMOVE: 
		default:	return ILLEGALMOVE;
					break;
	}

	// if king moved, update king position and disallow castling
	if(board[to] == 'k') {
		black_king = to;
		castling_flags &= ~(BKCASTLING | BQCASTLING);
	}
	else if (board[to] == 'K') {
		white_king = to;
		castling_flags &= ~(WKCASTLING | WQCASTLING);
	}

	// if rook moved, disallow appropriate castling
	if(board[to] == 'r' || board[to] == 'R') {
		switch(from) {
			case 0: //black queens rook
				castling_flags &= ~BQCASTLING;
				break;
			case 7: // black kings rook
				castling_flags &= ~BKCASTLING;
				break;
			case 56: // white queens rook
				castling_flags &= ~WQCASTLING;
				break;
			case 63: // white kings rook
				castling_flags &= ~WKCASTLING;
		}
	}

	// automaticaly promote pawn to a queen
	if((board[to] == 'p') && (to / ROWS  == ROWS - 1)) {
		board[to] = 'q';
		// give option to promote to something else
		// return PAWNPROMOTION
	}

	if((board[to] == 'P') && (to/ROWS == 0)) {
		board[to] = 'Q';
		// give option to promote to something else
		// return PAWNPROMOTION
	}
	
	int oc = (get_color(to) == WHITE) ? BLACK : WHITE;	
	vector<move_t> aom = all_moves(oc);
	if(king_checked(oc)) {
		if(aom.empty())
			return MATE;
		else
			return CHECK;
	} else if(aom.empty()) {
		return DRAW;
	}
		
	return REGULARMOVE;
}

/**
 * Calculates all posible pawn moves
 *
 * @param position pawn's position on the board
 * @return all possible moves
 */
vector<int> Board::pawn_moves(int position)
{
	vector<int> moves;
	int mf = (get_color(position) == WHITE) ? UP : DOWN; // move forward by 1 row
	int sp = (get_color(position) == WHITE) ? 6 : 1; // starting row possition (for checking 2 moves forward)
	int dest = position + mf;
	if(board[dest] == EMPTY) { // one forward
		moves.push_back(dest);
		dest += mf; 	
		if((position / ROWS == sp) && (board[dest] == EMPTY)) // two forward
			moves.push_back(dest);
	}

	// left attack
	if(position % ROWS > 0) { // check border
		dest = position + mf + LEFT;
		if((board[dest] != EMPTY) && !same_color(position, dest)) 
			moves.push_back(dest);
		else if((board[dest] == EMPTY) && (enpassant == dest)) {
		 	moves.push_back(dest);
		}
	} 
	
	// right attack
	if(position % ROWS < 7) { // check border
		dest = position + mf + RIGHT;
		if((board[dest] != EMPTY) && !same_color(position, dest))
			moves.push_back(dest);
		else if((board[dest] == EMPTY) && (enpassant == dest))
			moves.push_back(dest);
	}

	return moves;
}

/**
 * Calculates all posible rook moves
 *
 * @param position rook's position on the board
 * @return all possible moves
 */
vector<int> Board::rook_moves(int position)
{
	vector<int> moves;
	int row = position / ROWS;
	int dest = position + UP;

	// up 
	while(--row >= 0) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += UP;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}
	
	row = position / ROWS;
	dest = position + DOWN;
	// down
	while(++row < ROWS) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += DOWN;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	int col = position % ROWS;
	dest = position + LEFT;
	// left
	while(--col >= 0) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += LEFT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	col = position % ROWS;
	dest = position + RIGHT;
	//right
	while(++col < COLUMNS) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += RIGHT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	return moves;
}

/**
 * Calculates all posible knight moves
 *
 * @param position knight's position on the board
 * @return all possible moves
 */
vector<int> Board::knight_moves(int position) 
{
	vector<int> moves;
	int row = position / ROWS;
	int col = position % ROWS;
	
	// (2U, 1R)
	int dest = position + 2*UP + RIGHT;
	if((row - 2 >= 0) && (col + 1 < COLUMNS) && !same_color(position, dest))
		moves.push_back(dest);
	// (1U, 2R)
	dest = position + UP + 2*RIGHT;
	if((row - 1 >= 0) && (col + 2 < COLUMNS) && !same_color(position, dest))
		moves.push_back(dest);
	// (1D, 2R)
	dest = position + DOWN + 2*RIGHT;
	if((row + 1 < ROWS) && (col + 2 < COLUMNS) && !same_color(position, dest))
		moves.push_back(dest);
	// (2D, 1R)
	dest = position + 2*DOWN + RIGHT;
	if((row + 2 < ROWS) && (col + 1 < COLUMNS) && !same_color(position, dest))
		moves.push_back(dest);
	// (2D, 1L)
	dest = position + 2*DOWN + LEFT;
	if((row + 2 < ROWS) && (col - 1 >= 0) && !same_color(position, dest))
		moves.push_back(dest);
	// (1D, 2L)
	dest = position + DOWN + 2*LEFT;
	if((row + 1 < ROWS) && (col - 2 >= 0) && !same_color(position, dest))
		moves.push_back(dest);
	// (1U, 2L)
	dest = position + UP + 2*LEFT;
	if((row - 1 >= 0) && (col - 2 >= 0) && !same_color(position, dest))
		moves.push_back(dest);
	// (2U, 1L)
	dest = position + 2*UP + LEFT;
	if((row - 2 >= 0) && (col - 1 >= 0) && !same_color(position, dest))
		moves.push_back(dest);

	return moves;
}

/**
 * Calculates all posible bishop moves
 *
 * @param position bishop's position on the board
 * @return all possible moves
 */
vector<int> Board::bishop_moves(int position)
{
	vector<int> moves;
	int row = position / ROWS;
	int col = position % ROWS;
	
	// up right
	int dest = position + UP + RIGHT;
	while((--row >= 0) && (++col < COLUMNS)) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += UP + RIGHT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	row = position / ROWS;
	col = position % ROWS;
	// down right
	dest = position + DOWN + RIGHT;
	while((++row < ROWS) && (++col < COLUMNS)) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += DOWN + RIGHT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	row = position / ROWS;
	col = position % ROWS;
	// down left
	dest = position + DOWN + LEFT;
	while((++row < ROWS) && (--col >= 0)) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += DOWN + LEFT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	row = position / ROWS;
	col = position % ROWS;
	// up left
	dest = position + UP + LEFT;
	while((--row >= 0) && (--col >= 0)) {
		if(board[dest] == EMPTY) {
			moves.push_back(dest);
			dest += UP + LEFT;
		} else if(!same_color(position, dest)) {
			moves.push_back(dest);
			break;
		}
	}

	return moves;
}

/**
 * Calculates all posible queen moves
 *
 * @param position queen's position on the board
 * @return all possible moves
 */
vector<int> Board::queen_moves(int position)
{
	// combination of rook moves + bishop moves
	vector<int> rm = rook_moves(position);
	vector<int> bm = bishop_moves(position);
		
	rm.insert(rm.end(), bm.begin(), bm.end());
	return rm;
}

/**
 * Calculates all posible king moves
 *
 * @param position king's position on the board
 * @return all possible moves
 */
vector<int> Board::king_moves(int position)
{
	vector<int> moves;
	int row = position / ROWS;
	int col = position % ROWS;

	// up
	int dest = position + UP;
	if((row - 1 >= 0) && (!same_color(position, dest)))
		moves.push_back(dest);
	// up right
	dest = position + UP + RIGHT;
	if((row - 1 >= 0) && (col + 1 < COLUMNS) && (!same_color(position, dest)))
		moves.push_back(dest);
	// right
	dest = position + RIGHT;
	if((col + 1 < COLUMNS) && (!same_color(position, dest)))
		moves.push_back(dest);
	// down right
	dest = position + DOWN + RIGHT;
	if((row + 1 < ROWS) && (col + 1 < COLUMNS) && (!same_color(position, dest)))
		moves.push_back(dest);
	// down
	dest = position + DOWN;
	if((row + 1 < ROWS) && (!same_color(position, dest)))
		moves.push_back(dest);
	// down left
	dest = position + DOWN + LEFT;
	if((row + 1 < ROWS) && (col - 1 >= 0) && (!same_color(position, dest)))
		moves.push_back(dest);
	// left
	dest = position + LEFT;
	if((col - 1 >= 0) && (!same_color(position, dest)))
		moves.push_back(dest);
	// up left
	dest = position + UP + LEFT;
	if((row - 1 >= 0) && (col - 1 >= 0) && (!same_color(position, dest)))
		moves.push_back(dest);

	// castling
	unsigned kc = (get_color(position) == WHITE) ? castling_flags & WKCASTLING 
																: castling_flags & BKCASTLING;
	unsigned qc = (get_color(position) == WHITE) ? castling_flags & WQCASTLING
																: castling_flags & BQCASTLING;
	
	//king side
	col = position % ROWS;
	int f = position + RIGHT;
	if(kc) {
		while(col++ < COLUMNS) {
			if(board[f] != EMPTY)
				break;
			f += RIGHT;
		}
		if(col == COLUMNS - 1) 
			moves.push_back(position + 2*RIGHT);
	}

	col = position % ROWS;
	f = position + LEFT;
	// queen side
	if(qc) {
		while(col-- >= 0) {
			if(board[f] != EMPTY)
				break;
			f += LEFT;
		}
		if(col == 0)
			moves.push_back(position + 2*LEFT);
	}

	return moves;
}
