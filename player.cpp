#include "player.h"

player::player(string name)
{
	//make name const?
	playerName = name;

	this->resetBoard();
}

void player::resetBoard()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			playerBoard[i][j] = 0;

}

void player::modifyShips(int x, int y, string orientation, int shipType)
{

}

bool player::isWin()
{
	return true;
}

string player::getBoard(bool pNum)
{
	string temp = this->getName();

	for (int i = 0; i < 10; i++)
	{
		temp = temp + "\n";

		for (int j = 0; j < 10; j++)
		{
			if(playerBoard[i][j] == 0) //water
				temp = temp + "~" + " ";
			else if (playerBoard[i][j] == 1) //hit ship
				temp = temp + "X" + " ";
			else if (playerBoard[i][j] == 2) //missed ship
				temp = temp + "*" + " ";
			else if (playerBoard[i][j] >= 5 && pNum == true) //ship
				temp = temp + "O" + " ";
			
		}
	}

	return temp;
}

string player::getName()
{
	return playerName;
}

