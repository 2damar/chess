CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -pedantic

all: test

test: test.o board.o 
	$(CC) $(CCFLAGS) $^ -o $@

test.o: test.cc board.h
	$(CC) $(CCFLAGS) -c $< -o $@

board.o: board.cc board.h types.h
	$(CC) $(CCFLAGS) -c $< -o $@	

.PHONY: clean

clean:
	rm -f *.o
