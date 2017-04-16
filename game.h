#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <iostream>
#include <time.h>
#include <vector> 

using namespace std;


class Game {

	Player* p1;
	Player* p2;
	
	bool isTwoPlayers;
    bool AIsearching;
    int AIhit [2];
    int AItarget [2]; 
    vector<int> AItargetsX;
    vector<int> AItargetsY;
    bool searching = false;
    
public:
	Game();

	void printBoard(bool pNum);

	string checkHit(int loc1, int loc2, bool isP1);//(Mjarvis1997) changed from void to string

	void updateBoard(string loc1, string loc2);

	void placeShips(bool player, bool isTwoPlayers);

	void makePlayers(bool isTwoPlayers);//(Mjarvis1997) changed from "void makePlayer(bool pType)"

	int cleanInput(string input, int range);

	void fire(bool isP1);

	void gRound(bool isP);

	void gControl();
    
    void aiSearch();


};

#endif
