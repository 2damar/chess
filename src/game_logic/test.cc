#include "board_controller.h"

#include <iostream>

using namespace std;

int main()
{
	BoardController c;


	c.print_board();
	cout << " ----------- " << endl;
	vector<move_t> am = c.all_moves(WHITE);
	for(vector<move_t>::iterator it = am.begin(); it != am.end(); it++)
		cout << (*it).from << " -> " << (*it).to << endl;
	c.make_move(52, 36);
	c.print_board();
	am = c.all_moves(WHITE);
	for(vector<move_t>::iterator it = am.begin(); it != am.end(); it++)
		cout << (*it).from << " -> " << (*it).to << endl;
	
	return 0;
}


