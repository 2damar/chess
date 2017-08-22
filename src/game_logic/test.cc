#include "board_controller.h"

#include <iostream>

using namespace std;

int main()
{
	BoardController c;


	c.print_board();
	c.make_move(52, 36);
	cout << " ----------- " << endl;
	c.print_board();
	
	return 0;
}


