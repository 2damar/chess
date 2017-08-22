#include <iostream>
#include "board_controller.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::set;

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
	board.assign(64, '0');
}

/**
 * Initializes the board with the pieces
 * 
 * @param b board fields with pieces
 */
void BoardController::set_pieces(string b)
{
	if(b.size() != 64) 
		board = "rnbqkbnrpppppppp00000000000000000000000000000000PPPPPPPPRNBQKBNR";
	else 
		board = b;

	white_king = board.find('K');
	black_king = board.find('k');
}
		

/**
 * Returns the piece on the field or EMPTY
 * 
 * @param c index into the board
 * @return piece char or EMPTY
 */
char BoardController::get_field(int c)
{
	return board[c];
}

/**
 * Returns color of the piece
 *
 * @param c location of the piece
 * @return color of the piece, or EMPTY, if the field is empty
 */
int BoardController::get_color(int c)
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
bool BoardController::same_color(int p1, int p2)
{
	if(get_color(p1) != get_color(p2))
		return false;

	return true;
}

/**
 * Returns all legal directions in which piece can move
 * 
 * @param c position of the piece
 * @return flags with possible directions
 */
unsigned BoardController::get_piece_directions(int c)
{
	switch(board[c]) {
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
int BoardController::get_piece_steps(int c)
{
	char p = board[c];
	// kings and knights
	if(p == 'k' || p == 'K' || p == 'n' || p == 'N')
		return 1;
	
	// pawns 
	if(((p == 'p') && (c / ROWS == 1)) || ((p == 'P') && (c / ROWS == 6)))
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
vector<int> BoardController::piece_moves(int piece) 
{
	vector<int> vc;
	unsigned piece_directions = get_piece_directions(piece);
	int steps = get_piece_steps(piece);
	int dest;

	for(int i = 0; i < 16; i++) {
		if((piece_directions & (1 << i)) != 0) {
			
			coord_t c;
			c.row = (piece / ROWS) + directions[i].row;
			c.col = (piece % ROWS) + directions[i].col;
			int ex = 1;

			while((!out_of_bounds(c)) && (ex <= steps)) {
				dest = 8*c.row + c.col;
				if(board[dest] != EMPTY) {
					if(!same_color(piece, dest) && (board[piece] != 'p') && (board[piece] != 'P'))
						vc.push_back(dest);
					break;
				}

				vc.push_back(dest);
				++ex;
				c.row = (piece / ROWS) + ex*directions[i].row;
				c.col = (piece % ROWS) + ex*directions[i].col;
			}
		}
	}

	// pawn attack
	coord_t pa;
	if(board[piece] == 'p') {
		pa.row = (piece / ROWS) + 1;
		pa.col = (piece % ROWS) - 1;
		dest = 8*pa.row + pa.col;
		if(!out_of_bounds(pa) && !same_color(piece, dest) && board[dest] != EMPTY) 
			vc.push_back(dest);
		pa.col = (piece % ROWS) + 1;
		dest = 8*pa.row + pa.col;
		if(!out_of_bounds(pa) && !same_color(piece, dest) && board[dest] != EMPTY)
			vc.push_back(dest);
	}

	if(board[piece] == 'P') {
		pa.row = (piece / ROWS) - 1;
		pa.col = (piece % ROWS) - 1;
		dest = 8*pa.row + pa.col;
		if(!out_of_bounds(pa) && !same_color(piece, dest) && board[dest] != EMPTY)
			vc.push_back(dest);
		pa.col = (piece % ROWS) + 1;
		dest = 8*pa.row + pa.col;
		if(!out_of_bounds(pa) && !same_color(piece, dest) && board[dest] != EMPTY)
			vc.push_back(dest);
	}

	
	return vc;
}

/**
 * Returns all the field that can player possibly attack
 * 
 * @param color color of the players pieces
 * @return vector of covered fields
 */
set<int> BoardController::covered_fields(int color)
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
vector<move_t> BoardController::all_moves(int color)
{
	vector<move_t> am;
	vector<int> pm;
	string pieces = (color == WHITE) ? "RNBQKP" : "rnbqkp";
	for(int i = 0; i < ROWS * COLUMNS; i++) {
		if(pieces.find(board[i]) != string::npos) {
			pm = piece_moves(i);
			for(vector<int>::iterator it = pm.begin(); it != pm.end(); it++) {
				if(try_move(i, *it)) 
					am.push_back({board[i], board[*it], i, *it});
			}
		}
	}

	return am;
}

/**
 * Simulates the move and finds out if it is possible to make it
 * 
 * @param from starting position
 * @param to destination
 * @return true if move is possible, otherwise false
 */
bool BoardController::try_move(int from, int to)
{
	if(!legal_move(from, to))
		return false;
	
	//simulate the move and find out if the king will be in check
	int kc = (get_color(from) == WHITE) ? WHITE : BLACK;
	char to_piece = board[to];
	board[to] = board[from];
	board[from] = EMPTY;
	if(board[to] == 'k')
		black_king = to;
	else if(board[to] == 'K')
		white_king = to;
	
	bool result = !king_checked(kc);
	board[from] = board[to];
	board[to] = to_piece;
	if(board[from] == 'k')
		black_king = from;
	else if(board[from] == 'K')
		white_king = from;

	return result;
}


	
	
/**
 * Checks if the move is possible
 * @param from location of the piece
 * @param to destination where should be piece moved
 * @return true when the move is legal, otherwise false
 */
bool BoardController::legal_move(int from, int to)
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
int BoardController::make_move(int from, int to)
{	
	if(!try_move(from, to))
		return ILLEGALMOVE;

	move_t m = { board[from],
					 board[to],
					 from,
					 to };
	
	board[to] = board[from];
	board[from] = EMPTY;
	game_moves.push_back(m);

	if(board[to] == 'k') 
		black_king = to;
	else if (board[to] == 'K') 
		white_king = to;

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
		
	return LEGALMOVE;
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
	board[m.from] = m.piece_from;
	board[m.to] = m.piece_to;

	if(board[m.from] == 'k') 
		black_king = m.from;
	else if(board[m.from] == 'K') 
		white_king = m.from;

	game_moves.pop_back();
	return 1;
}

void BoardController::print_board() 
{
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++) 
			cout << "|" << board[8*i + j];
		cout << "|" << endl;
	}
}
