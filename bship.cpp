

#include "game.h"

using namespace std;

int main() {

	Game* g1 = new Game();

	//g1->printBoard(true); //p1 board
	//g1->printBoard(false); //p2 board

	//need a loop with a win check
	g1->gControl;
	
	delete g1;// need deconstructor

	return 0;
}
