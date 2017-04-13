#include "game.h"


game::game()
{
	string temp;

	
	cout << "Make a new game" << endl;
	cout << "1 or 2 players" << endl;
	//add code for that here

	if (true) // 2 players, else is 1 and comp
	{
		cout << "Player 1 enter name:" << endl;
		cin >> temp;
		p1 = new player(temp);

		temp = "";

		cout << "Player 2 enter name:" << endl;
		cin >> temp;
		p2 = new player(temp);
	}
	else
	{
		//make player one and comp
	}
	
}

//deconstructor?

void game::printBoard(bool pNum)
{
	string temp = "";

	if(pNum == true)
	{
		temp = p1->getBoard(true);
		temp = temp + "\n\n";
		temp = temp + p2->getBoard(false);
	}
	else
	{
		temp = p1->getBoard(false);
		temp = temp + "\n\n";
		temp = temp + p2->getBoard(true);
	}

	cout << temp << endl;
}

void game::fire()
{
	string temp = "";
	string temp2 = "";

	cout << "Please select x" << endl;
	cin >> temp;
	cout << "Please select y" << endl;
	cin >> temp2;

	//cout << cleanInput(temp) << endl;
	//cout << cleanInput(temp2) << endl;
}

void game::checkHit(string loc1, string loc2)
{
		//used by fire method
}

void game::updateBoard(string loc1, string loc2)
{

}

//uses set method in player class modifyShips((int x, int y, string orientation, int shipType)
void game::placeShips()
{

}

void game::makePlayer(bool pType)
{
	//for making comp player
}

//everytime taking in cord info as string
int game::cleanInput(string input)
{
	int t1;
	int t2;

	//does not yet check if string num is num 1-10

	t1 = input[0];
	t1 -= 48;

	if (input.size() > 1) {
		t2 = input[1];
		t2 -= 48;
	
		t1 *= 10;
		t1 += t2;

	}
	
	return t1;
}

//used by bship to run game
void game::gRound(bool isP) //true = p1
{
	//game turn logic.
}

