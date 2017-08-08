#include "chess_controller.h"

#include <iostream>

using namespace std;

int main()
{
	ChessController c;

	coord_t f = {6, 4};
	coord_t t = {5, 4};

	c.print_board();
	c.make_move(f, t);
	cout << " ----------- " << endl;
	c.print_board();
	
	return 0;
}


