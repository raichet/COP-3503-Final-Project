#include "player.h"

Player::Player(string name)
{
	//make name const?
	playerName = name;

	this->resetBoard();
}

void Player::resetBoard()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			playerBoard[i][j] = 0;

}

//modifyShips method assumes correct data type of arguments, but not correct range
//modifyShips method will return false if x/y is out of range, orientation is not a valid direction, or shipType is out of range
bool Player::modifyShips(int x, int y, string orientation, int shipType)
{
	int shipLength;

	if (shipType == 5) {
		shipLength = 5;
	} else if (shipType == 6) {
		shipLength = 4;
	} else if (shipType == 7) {
		shipLength = 3;
	} else if (shipType == 8 || shipType == 9) {
		shipLength = 2;
	} else {
		cout << "Invalid input for variable shipType" << endl;
		return false;
	}

	if (x > 10 || y > 10 || x < 1 || y < 1) {
		cout << "Anchor point out of range" << endl;
		return false;
	}

	if (orientation.compare("right") == 0) {
		if (shipLength > (10 - x + 1)) {
			cout << "Ship runs off right edge of board" << endl;
			return false;
		}
		else {
			for (int i = x - 1; i < (x - 1) + shipLength; i++) {
				if (playerBoard[i][y - 1] != 0) {
					cout << "The space (" << i << "," << y << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = x - 1; i < (x - 1) + shipLength; i++) {
				playerBoard[i][y - 1] = shipType;
			}
			return true;
		}
	}
	else if (orientation.compare("left") == 0) {
		if (shipLength > x) {
			cout << "Ship runs off left edge of board" << endl;
			return false;
		}
		else {
			for (int i = x - 1; i > (x - 1) - shipLength; i--) {
				if (playerBoard[i][y - 1] != 0) {
					cout << "The space (" << i << "," << y << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = x - 1; i > (x - 1) - shipLength; i--) {
				playerBoard[i][y - 1] = shipType;
			}
			return true;
		}
	}
	else if (orientation.compare("down") == 0) {
		if (shipLength > (10 - y + 1)) {
			cout << "Ship runs off bottom edge of board" << endl;
			return false;
		}
		else {
			for (int i = y - 1; i < (y - 1) + shipLength; i++) {
				if (playerBoard[x - 1][i] != 0) {
					cout << "The space (" << x << "," << i << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = y - 1; i < (y - 1) + shipLength; i++) {
				playerBoard[x - 1][i] = shipType;
			}
			return true;
		}
	}
	else if (orientation.compare("up") == 0) {
		if (shipLength > y) {
			cout << "Ship runs off top edge of board" << endl;
			return false;
		}
		else {
			for (int i = y - 1; i > (y - 1) - shipLength; i--) {
				if (playerBoard[x - 1][i] != 0) {
					cout << "The space (" << x << "," << i << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = y - 1; i > (y - 1) - shipLength; i--) {
				playerBoard[x - 1][i] = shipType;
			}
			return true;
		}
	}

	else {
		cout << orientation + " is an invalid ship orientation."<< endl;
		return false;
	}
}

bool Player::isWin()
{
	if (playerShips[0] == 0 && playerShips[1] == 0 && playerShips[2] == 0 && playerShips[3] == 0 && playerShips[4] == 0)
		return true;
	else
		return false;
}

string Player::getBoard(bool pNum)
{
	string temp = "\nPlayer name: "+this->getName();

	for (int i = 0; i < 10; i++)
	{
		temp = temp + "\n";

		if (i==0) 	//formats the grid with top row of
		{
			temp=temp+"0 ";
		for (int k=1 ; k<=10 ; k++)
		{
			temp=temp+" "+to_string(k)+" ";
		}
		temp=temp+"\n";
	}				////numbering system

		for (int j = 0; j < 10; j++)
		{
		if (j==0 && i==9) //formats the grid with left column of
		{
			temp=temp+to_string(i+1)+"";
		}
		else if (j==0 && i!=9)
		{
			temp=temp+to_string(i+1)+" ";
		}
			if(playerBoard[j][i] == 0) //water
// Emoji display
				temp = temp + " 🌊" + " ";
			else if (playerBoard[j][i] == 1) //hit ship
				temp = temp + " 💥" + " ";
			else if (playerBoard[j][i] == 2) //missed ship
				temp = temp + " ❌" + " ";
			else if (playerBoard[j][i] >= 5 && pNum == true) //ship
			{
				if (playerBoard[j][i] == 5)
				{
					temp = temp + " 🚢" + " ";
				}
				else if (playerBoard[j][i] == 6)
				{
					temp = temp + " 🛳️" + " ";
				}
				else if (playerBoard[j][i] == 7)
				{
					temp = temp + " ⛴" + " ";
				}
				else if (playerBoard[j][i] == 8)
				{
					temp = temp + " ⛵" + " ";
				}
				else if (playerBoard[j][i] == 9)
				{
					temp = temp + " 🚣🏿‍♀️" + " ";
				}
			}
			else
				temp = temp + " 🌊" + " ";
//  Non-emoji display
// 				temp = temp + " ~" + " ";
// 			else if (playerBoard[j][i] == 1) //hit ship
// 				temp = temp + " X" + " ";
// 			else if (playerBoard[j][i] == 2) //missed ship
// 				temp = temp + " *" + " ";
// 			else if (playerBoard[j][i] >= 5 && pNum == true) //ship
// 				temp = temp + " O" + " ";
// 			else
// 				temp = temp + " ~" + " ";


		}
		//--------------------Test print grid with numbers--------------------
		// for (int j = 0; j < 10; j++)
		// {
		// 	if (j==0 && i==9) //formats the grid with left column of
		// 	{
		// 		temp=temp+to_string(i+1)+" ";
		// 	}
		// 	else if (j==0 && i!=9)
		// 	{
		// 		temp=temp+to_string(i+1)+"  ";
		// 	}				  //numbering system
		// 	if(playerBoard[j][i] == 0) //water
		// 		temp = temp + " 0" + " ";
		// 	else if (playerBoard[j][i] == 1) //hit ship
		// 		temp = temp + " 1" + " ";
		// 	else if (playerBoard[j][i] == 2) //missed ship
		// 		temp = temp + " 2" + " ";
		// 	else if (playerBoard[j][i] >= 5 && pNum == true) //ship
		// 	{
		// 		if (playerBoard[j][i] == 5)
		// 		{
		// 			temp = temp + " 5" + " ";
		// 		}
		// 		else if (playerBoard[j][i] == 6)
		// 		{
		// 			temp = temp + " 6" + " ";
		// 		}
		// 		else if (playerBoard[j][i] == 7)
		// 		{
		// 			temp = temp + " 7" + " ";
		// 		}
		// 		else if (playerBoard[j][i] == 8)
		// 		{
		// 			temp = temp + " 8" + " ";
		// 		}
		// 		else if (playerBoard[j][i] == 9)
		// 		{
		// 			temp = temp + " 9" + " ";
		// 		}
		// 	}
		// 	else
		// 		temp = temp + " ~" + " ";
		//
		// }
		//--------------------------------------------------------------------
	}

	return temp;
}

string Player::getName()
{
	return playerName;
}

int Player::getPlayerShipTypes(int index) {
	return playerShipTypes[index];
}

int Player::getPlayerShips(int index) {
	return playerShips[index];
}

int Player::getBoardValue (int loc1, int loc2) {
		return playerBoard[loc1-1][loc2-1];
}

void Player::updateBoard(int loc1, int loc2, int result, int shipType) {
	playerBoard[loc1-1][loc2-1] = result;

	if (shipType > 4 && shipType < 10)
	{
		for(int i = 0; i < 5; i++) //use array size instead of hardcoded 5 for better standard and dynamic ship number
		{
			if(shipType == playerShipTypes[i] && playerShips[i] != 0)
			{
				playerShips[i]--;
			}
		}
	}
	// no error code if it does not find maching value
}
