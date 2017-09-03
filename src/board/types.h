#ifndef TYPES_H
#define TYPES_H

#include <string>

#define ROWS 8
#define COLUMNS 8

#define UP (-8)
#define RIGHT 1
#define DOWN 8
#define LEFT (-1)
#define EMPTY '0'
#define BLACK 1
#define WHITE 2

#define ILLEGALMOVE 0
#define REGULARMOVE 1
#define KINGCASTLING 2
#define QUEENCASTLING 3
#define ENPASSANT 4
#define PAWNTWOFORWARD 5
#define PAWNPROMOTION 6

#define CHECK 7 
#define MATE 8
#define DRAW 9

#define WKCASTLING 0x01
#define WQCASTLING 0x02
#define BKCASTLING 0x04
#define BQCASTLING 0x08

typedef struct board_features {
	std::string board;           ///< board
	unsigned cf;					  ///< castling flags
	int ep;							  ///< en passant
	int ap;							  ///< active player
} board_features_t;

#endif
