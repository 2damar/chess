#ifndef TYPES_H
#define TYPES_H

#define ROWS 8
#define COLUMNS 8
#define UPLEFT 0
#define UP 1
#define UPRIGHT 2
#define LEFT 3
#define NOMOVE 4
#define RIGHT 5
#define DOWNLEFT 6
#define DOWN 7
#define DOWNRIGHT 8
#define NM1 9
#define NM2 10
#define NM3 11
#define NM4 12
#define NM5 13
#define NM6 14
#define NM7 15
#define NM8 16

#define EMPTY '0'
#define BLACK 1
#define WHITE 2


typedef struct coord {
	int row;
	int col;
} coord_t;



#endif
