CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -pedantic

all: test

test: test.o chess_controller.o board.o 
	$(CC) $(CCFLAGS) $^ -o $@

test.o: test.cc chess_controller.h
	$(CC) $(CCFLAGS) -c $< -o $@

chess_controller.o: chess_controller.cc chess_controller.h types.h
	$(CC) $(CCFLAGS) -c $< -o $@	

board.o: board.cc types.h
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o
