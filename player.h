#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

using namespace std;

class Player {

	string playerName;

	int playerBoard[10][10];
	
	int playerShipTypes[5] = {5, 6, 7, 8, 9}; 

	int playerShips[5] = { 5,4,3,2,2 };//(MJarvis1997) Assigns known HP values right off the bat

	bool winning;

public:
	Player(string name);

	void resetBoard();

	bool modifyShips(int x, int y, string orientation, int shipType);

	bool isWin();

	string getBoard(bool pNum);

	string getName();

	int getPlayerShipTypes(int index);
	
	int getPlayerShips(int index);
	
	int getBoardValue(int loc1, int loc2);
	
	void updateBoard(int loc1, int loc2, int result, int shipType);

};

#endif
