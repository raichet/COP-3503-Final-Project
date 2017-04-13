

#include "game.h"

using namespace std;

int main() {

	game* g1 = new game();

	g1->printBoard(true); //p1 board
	g1->printBoard(false); //p2 board

	//need a loop with a win check
	//g1->gRound(true); //true is player 1

	return 0;
}
