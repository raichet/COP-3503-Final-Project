#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {

	string playerName;

	int playerBoard[10][10];

	int playerShips[] = { 5,4,3,2,2 };//(MJarvis1997) Assigns known HP values right off the bat

	bool winning;

public:
	player(string name);

	void resetBoard();

	bool modifyShips(int x, int y, string orientation, int shipType);

	bool isWin();

	string getBoard(bool pNum);

	string getName();

	int getPlayerShips(int index);

};

#endif
