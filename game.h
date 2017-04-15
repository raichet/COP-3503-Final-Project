#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <iostream>
#include <time.h>

using namespace std;


class Game {

	Player* p1;
	Player* p2;
	
	bool isTwoPlayers;

public:
	Game();

	void printBoard(bool pNum);

	string checkHit(int loc1, int loc2, bool isP1);//(Mjarvis1997) changed from void to string

	void updateBoard(string loc1, string loc2);

	void placeShips(bool player);

	void makePlayers(bool isTwoPlayers);//(Mjarvis1997) changed from "void makePlayer(bool pType)"

	int cleanInput(string input, int range);

	void fire(bool isP1);

	void gRound(bool isP);

	void gControl();


};

#endif
