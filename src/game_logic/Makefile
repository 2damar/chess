CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -pedantic

all: test

test: test.o board_controller.o 
	$(CC) $(CCFLAGS) $^ -o $@

test.o: test.cc board_controller.h
	$(CC) $(CCFLAGS) -c $< -o $@

board_controller.o: board_controller.cc board_controller.h types.h
	$(CC) $(CCFLAGS) -c $< -o $@	

.PHONY: clean

clean:
	rm -f *.o
