#ifndef GAME_H
#define GAME_H	 

#include "player.h"
#include <iostream>
#include <time.h>

using namespace std;


class game {

	player* p1;
	player* p2;

public:
	game();

	void printBoard(bool pNum);

	void checkHit(string loc1, string loc2);

	void updateBoard(string loc1, string loc2);

	void placeShips();

	void makePlayer(bool pType);

	int cleanInput(string input);

	void fire();

	void gRound(bool isP);


};

#endif
