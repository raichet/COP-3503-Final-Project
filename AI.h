#ifndef AI_H
#define AI_H

#include <string>

using namespace std;

class AI {

	string difficulty; //Either 'Easy' or 'Hard'

	int AIBoard[10][10];

	int AIShips[] = { 5,4,3,2,2 };

	bool winning;

public:
	AI(string difficulty);

	void resetBoard();

	void modifyShips();

	bool isWin();
	
	string getBoard();
	
	int getAIShips(int index);

	void attack(string difficulty); // Attacks the player using specified algorithm
                                  // 'Easy' describes randomly selecting every space; 'Hard' describes selecting spaces at random and when a space is hit, intuitively selecting spaces around the hit space
};

#endif
