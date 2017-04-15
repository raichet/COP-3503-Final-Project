#ifndef AI_H
#define AI_H

#include <string>

using namespace std;

class AI {

	string difficulty; 

	string playerName;

	int AIBoard[10][10];

	int AIShips[] = { 5,4,3,2,2 };

	bool winning;



public:
	AI(string difficulty);

	string getName();

	void resetBoard();

	void modifyShips(int x, int y, string orientation, int shipType);

	string getBoard(bool AI);

	int getBoardValue(int loc1, int loc2);

	int updateBoard(int loc1, int loc2, int result);

	bool isWin();

	void attack(string difficulty); // Attacks the player using specified algorithm 
};

#endif
