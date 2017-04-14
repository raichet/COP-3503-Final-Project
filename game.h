#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <iostream>
#include <time.h>

using namespace std;


class Game {

	player* p1;
	player* p2;

public:
	game();

	void printBoard(bool pNum);

	string checkHit(string loc1, string loc2);//(Mjarvis1997) changed from void to string

	void updateBoard(string loc1, string loc2);

	void placeShips();

	void makePlayers(bool isTwoPlayers);//(Mjarvis1997) changed from "void makePlayer(bool pType)"

	int cleanInput(string input);

	void fire();

	void gRound(bool isP);


};

#endif
