CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -pedantic
OBJ_DIR=../../obj

all: board.o

board.o: board.cc board.h types.h
	$(CC) $(CCFLAGS) -c $< -o $(OBJ_DIR)/$@	

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/board.o
