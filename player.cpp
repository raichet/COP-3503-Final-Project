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
	} else if (shipType == 8) {
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
				if (playerBoard[i][y] == shipType) {
					cout << "The space (" << i << "," << y << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = x - 1; i < (x - 1) + shipLength; i++) {
				playerBoard[i][y] = shipType;
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
				if (playerBoard[i][y] != 0) {
					cout << "The space (" << i << "," << y << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = x - 1; i > (x - 1) - shipLength; i--) {
				playerBoard[i][y] = shipType;
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
				if (playerBoard[x][i] != 0) {
					cout << "The space (" << x << "," << i << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = y - 1; i < (y - 1) + shipLength; i++) {
				playerBoard[x][i] = shipType;
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
				if (playerBoard[x][i] != 0) {
					cout << "The space (" << x << "," << i << ") was already occupied." << endl;
					return false;
				}
			}
			for (int i = y - 1; i > (y - 1) - shipLength; i--) {
				playerBoard[x][i] = shipType;
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

string Player::getName()
{
	return playerName;
}

int Player::getPlayerShips(int index) {
	return playerShips[index];
}

int Player::getBoardValue (int loc1, int loc2) {
		return playerBoard[loc1][loc2];
}

void Player::updateBoard(int loc1, int loc2, int result) {
	playerBoard[loc1][loc2] = result;
}
