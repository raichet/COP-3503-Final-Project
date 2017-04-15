#include "AI.h"
#include <string>
#include <vector> 
#include <algorithm>

AI::AI(string difficulty){
	
	playerName = "Computer";
	this -> resetboard();
}

void AI::resetBoard()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			AIBoard[i][j] = 0;

}

string AI::getName(){
	return playerName;
}

void AI::modifyShips(intx, int y, string orientation, int shipType){
	//Implement AI to randomly place ships 
}

bool AI::isWin(){
	return true;
}

string AI::getBoard(bool AI){
	string temp = this->getName();

	for (int i = 0; i < 10; i++)
	{
		temp = temp + "\n";

		for (int j = 0; j < 10; j++)
		{
			if(AIBoard[i][j] == 0) //water
				temp = temp + "~" + " ";
			else if (AIBoard[i][j] == 1) //hit ship
				temp = temp + "X" + " ";
			else if (AIBoard[i][j] == 2) //missed ship
				temp = temp + "*" + " ";
			else if (AIBoard[i][j] >= 5 && pNum == true) //ship
				temp = temp + "O" + " ";

		}
	}

	return temp;
}


int AI::getBoardValue(int loc1, int loc2){

	return AIBoard[loc1][loc2];
}

int AI::updateBoard(int loc1, int loc2, int result){

	AIBoard[loc1][loc2] = result;
}

void AI::attack(string difficulty){
	
	switch (difficulty){
		
		case easy: 
			//Randomly generate hits without repeating
		case hard: 
			//Implement AI algorithm to attack here

	}

}
