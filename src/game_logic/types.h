#ifndef TYPES_H
#define TYPES_H

#define ROWS 8
#define COLUMNS 8
#define UPRIGHT (1 << 0)
#define UP (1 << 1)
#define UPLEFT (1 << 2)
#define LEFT (1 << 3)
#define RIGHT (1 << 4)
#define DOWNLEFT (1 << 5)
#define DOWN (1 << 6)
#define DOWNRIGHT (1 << 7)
#define NM1 (1 << 8)
#define NM2 (1 << 9)
#define NM3 (1 << 10)
#define NM4 (1 << 11)
#define NM5 (1 << 12)
#define NM6 (1 << 13)
#define NM7 (1 << 14)
#define NM8 (1 << 15)

#define KINGDIRECTIONS (UPLEFT | UP | UPRIGHT | LEFT | RIGHT | DOWNLEFT | DOWN | DOWNRIGHT)
#define QUEENDIRECTIONS (UPLEFT | UP | UPRIGHT | LEFT | RIGHT | DOWNLEFT | DOWN | DOWNRIGHT)
#define ROOKDIRECTIONS (UP | DOWN | LEFT | RIGHT)
#define KNIGHTDIRESTIONS (NM1 | NM2 | NM3 | NM4 | NM5 | NM6 | NM7 | NM8)
#define BISHOPDIRECTIONS (UPRIGHT | UPLEFT | DOWNRIGHT | DOWNLEFT)
#define BLACKPAWNDIRECTIONS (DOWN)
#define WHITEPAWNDIRECTIONS (UP)

#define UPRIGHTINDEX 0
#define UPINDEX 1
#define UPLEFTINDEX 2
#define LEFTINDEX 3
#define RIGHTINDEX 4
#define DOWNLEFINDEX 5
#define DOWNINDEX 6
#define DOWNRIGHTINDEX 7
#define NM1INDEX 8
#define NM2INDEX 9
#define NM3INDEX 10
#define NM4INDEX 11
#define NM5INDEX 12
#define NM6INDEX 13
#define NM7INDEX 14
#define NM8INDEX 15

#define MAXDIRECTIONS 16

#define EMPTY '0'
#define BLACK 1
#define WHITE 2

#define ILLEGALMOVE 0
#define LEGALMOVE 1
#define CHECK 2
#define MATE 3
#define DRAW 4


typedef struct coord {
	int row;
	int col;
} coord_t;


#endif
