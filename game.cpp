#include "game.h"


Game::Game()//initiates game by deterimining # of players, and creating player objects accordingly
{
	string choice="0";
	isTwoPlayers=false;

	cout << "Welcome to Battleship!" << endl;
	cout << "Please choose the number of player(s). (1 or 2): ";
	//add code for that here

	while (choice!="1" && choice!="2")
	{
		cin >> choice;//(MJarvis1997) Added input to establish the # of players with bool isTwoPlayers
		if (choice == "1")
		{
			isTwoPlayers = false;
		}
		else if (choice == "2")
		{
			isTwoPlayers = true;
		}
		else
		{
			cout<<"Invalid input. Please only type in 1 or 2 to specify number of players: ";
		}
	}
	cout<<"The game will now start."<<endl;
	makePlayers(isTwoPlayers);


}

//deconstructor?

void Game::printBoard(bool isP1)
{
	string temp = "";

	if (isP1)
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

void Game::fire(bool isP1)//determines coordinates of fire position(whether from a realPlayer or an AI) and then uses checkHit and updateBoard to make the according changes
						  //(Mjarvis1997) added bool parameter so that game.fire can be used for both real and computer players
{
	
	string temp;
	string temp2;

	if (isP1)//(Mjarvis1997) fires for first player
	{
		cout << "Please select x" << endl;
		cin >> temp;
		cout << "Please select y" << endl;
		cin >> temp2;
		checkHit(cleanInput(temp, 2), cleanInput(temp2, 2), isP1);

			//cout << cleanInput(temp) << endl;
			//cout << cleanInput(temp2) << endl;
	}
	if ((!isP1) && isTwoPlayers)//(Mjarvis1997) fires for real second player
	{
		cout << "Please select x" << endl;
		cin >> temp;
		cout << "Please select y" << endl;
		cin >> temp2;
		checkHit(cleanInput(temp, 2), cleanInput(temp2, 2), isP1);
	}
	else
	{
		// algorith for AI firing

	}

}
//(Mjarvis1997) changed function type to string, so it can return the results of the hit, added currentPlayer parameter
//added all the if statements to update the board based on the check
string Game::checkHit(int loc1, int loc2, bool isP1)//(Mjarvis1997) determines if the chosen location is a hit/miss or has been already chosen
{
	//used by fire method
	if (isP1)
	{
		if ((p2->getBoardValue(loc1, loc2)) == 0)//hit water
		{
			p2->updateBoard(loc1, loc2, 2);//marks missed ship with value of 2
			return "miss";

		}
		if ((p2->getBoardValue(loc1, loc2)) == 1)//already hit ship here
		{
			return "already hit";
		}
		if ((p2->getBoardValue(loc1, loc2)) == 2)//already missed here
		{
			return " already miss";
		}
		if ((p2->getBoardValue(loc1, loc2)) >= 5)//hit a ship
		{
			p2->updateBoard(loc1, loc2, 1);//marks hit ship with value of 1
			return "hit";
		}
	}
	else
	{
		if ((p1->getBoardValue(loc1, loc2)) == 0)//hit water
		{
			p1->updateBoard(loc1, loc2, 2);//marks missed ship with value of 2
			return "miss";

		}
		if ((p1->getBoardValue(loc1, loc2)) == 1)//already hit ship here
		{
			return "already hit";
		}
		if ((p1->getBoardValue(loc1, loc2)) == 2)//already missed here
		{
			return " already miss";
		}
		if ((p1->getBoardValue(loc1, loc2)) >= 5)//hit a ship
		{
			p1->updateBoard(loc1, loc2, 1);//marks hit ship with value of 1
			return "hit";
		}
	}
	return "error bool isP1 not assigned properly";
}



//uses set method in player class modifyShips((int x, int y, string orientation, int shipType)
//if parameter "player" is true, then player 1's board is being modified
//otherwise if "player" is false, then player 2's board is being modified
//assumes that player is inputting anchorpoints (x,y) in form "x y". Does not assume valid input
void Game::placeShips(bool player)
{
	int anchorPointX;
	int anchorPointY;
	int shipsPlacedCounter = 0;
	string orientation;
	bool validPlacement = false;

	if (player) {
		while (shipsPlacedCounter < 5) {
			while (!validPlacement) {
				cout << "Place your ship of length " << p1->getPlayerShips(shipsPlacedCounter) << ". What are the x and y coordinates?: " << endl;
				cin >> anchorPointX >> anchorPointY;
				cout << "What is the orientation of the ship?" << endl;
				cin >> orientation;
				validPlacement = p1->modifyShips(anchorPointX, anchorPointY, orientation, p1->getPlayerShips(shipsPlacedCounter));
			}
		}
	} else {
		while (shipsPlacedCounter < 5) {
			while (!validPlacement) {
				cout << "Place your ship of length " << p2->getPlayerShips(shipsPlacedCounter) << ". What are the x and y coordinates?: " << endl;
				cin >> anchorPointX >> anchorPointY;
				cout << "What is the orientation of the ship?" << endl;
				cin >> orientation;
				validPlacement = p2->modifyShips(anchorPointX, anchorPointY, orientation, p2->getPlayerShips(shipsPlacedCounter));
			}
		}
	}
}


void Game::makePlayers(bool isTwoPlayers)//(Mjarvis1997)changed pType to isTwoPlayers
{
	//for making comp player
	//(Mjarvis1997) moved this here from game function to consolidate all the player creation to this makePlayer function
	if (isTwoPlayers) // 2 players, else is 1 and comp
	{
		string temp;
		cout << "Player 1 enter name: " << endl;
		cin >> temp;
		p1 = new Player(temp);

		temp = "";

		cout << "Player 2 enter name: " << endl;
		cin >> temp;
		p2 = new Player(temp);
	}
	else//(MJarvis1997)Filled in this else statement to create 1 player of inputted name, and also to create an AI player object
	{
		string temp;
		cout << "Player 1 enter name:" << endl;
		cin >> temp;
		p1 = new Player(temp);

		temp = "";

		cout << "A 'BattleBot' has been created for you to test your skills against!";
			p2 = new Player("BattleBot");
	}

}

//everytime taking in cord info as string
int Game::cleanInput(string input, int range)
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

	if (t1 < 1 || t1 > range)
		t1 = -1;


	return t1;
}

//used by bship to run game
void Game::gRound(bool isP1) //true = p1
{
	//clear board method
	//cout << "\033[2J\033[1;1H";?

	if(isP1)
		cout << "Player 1's turn!" << endl;
	else
		cout << "Player 2's turn!" << endl;

	if(isTwoPlayers)
	{
		cout << "Press Y when ready!" << endl;
		int x;
		cin >> x;//maybe make not sucky

		printBoard(isP1);

		fire(isP1);
	}
	//else for a.i.
}

void Game::gControl() //true = p1
{
	bool playerBool = true;

	//some ship place method here
	

	while (p1->isWin() == false && p2->isWin() == false)
	{
		gRound(playerBool);

		if (playerBool == true)
			playerBool = false;
		else
			playerBool = true;
	}

	if (p1->isWin() == true) //true means lose
	{
		cout << "player 2 wins!\n";
	}
	else
	{
		cout << "player 1 wins!\n";
	}
	delete p1;
	delete p2;
}
