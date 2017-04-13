#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class player {

	string playerName;

	int playerBoard[10][10];

	int playerShips[5];

	bool winning;

public:
	player(string name);

	void resetBoard();

	void modifyShips(int x, int y, string orientation, int shipType);

	bool isWin();

	string getBoard(bool pNum);

	string getName();

};

#endif


