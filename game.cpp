#include "game.h"


Game::Game()//initiates game by deterimining # of players, and creating player objects accordingly
{
	string choice="0";
	isTwoPlayers=false;

	cout << "\033[1;31mWelcome to Battleship!\033[0m" << endl;
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
	else if (!isP1 && isTwoPlayers)
	{
		temp = p1->getBoard(false);
		temp = temp + "\n\n";
		temp = temp + p2->getBoard(true);
	}
	else if (!isP1 && !isTwoPlayers)
	{
		cout << "Battlebot is thinking." << endl;
	}

	cout << temp << endl;
}

void Game::fire(bool isP1)//determines coordinates of fire position(whether from a realPlayer or an AI) and then uses checkHit and updateBoard to make the according changes
//(Mjarvis1997) added bool parameter so that game.fire can be used for both real and computer players
{
	int temp;
	int temp2;

	if (isP1)//(Mjarvis1997) fires for first player
	{
		cout << "Please choose a location to strike. What are the x and y coordinates? " << endl;
		cin >> temp >>temp2;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore(256,'\n');
			cout<<"Please only input whole numbers for both x and y coordinates."<<endl;
			cin >> temp >> temp2;
		}

		cout << checkHit(temp, temp2, isP1) << endl;

		//cout << cleanInput(temp) << endl;
		//cout << cleanInput(temp2) << endl;
	}
	if ((!isP1) && isTwoPlayers)//(Mjarvis1997) fires for real second player
	{
		cout << "Please choose a location to strike. What are the x and y coordinates? " << endl;
		cin >> temp >>temp2;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore(256,'\n');
			cout<<"Please only input whole numbers for both x and y coordinates."<<endl;
			cin >> temp >> temp2;
		}
		cout << checkHit(temp, temp2, isP1) << endl;
	}

	else if((!isP1) && !isTwoPlayers)
	{


		//Randomly picks coordinates
		if (searching==false)
		{
			srand (time(NULL));
			temp = rand() % 10 + 1;
			srand (time(NULL));
			temp2 = rand() % 10 + 1;
			if (checkHit(temp, temp2, isP1).compare("hit") == 0)
			{
				cout << "Battlebot Hit" << endl;
				searching = true;
				AIhit[0] = temp;
				AIhit[1] = temp2;
				//Adds surrounding spaces to aiTargets vector
				aiSearch();
				searching=false;
			}
			else
			{
				cout<< "Battlebot Missed"<< endl;
				searching = false;
			}

		}
		//
		else
		{
			//choose hits from vector aiTargets

			temp = AItargetsX.front();//first value of vector x position
			temp2 = AItargetsY.front();//second value of vector y position
			AItargetsX.erase(AItargetsX.begin());
			AItargetsY.erase(AItargetsY.begin());
			if (checkHit(temp, temp2, isP1).compare("hit") == 0)
			{
				searching = true;
				AIhit[0] = temp;
				AIhit[1] = temp2;
				//Adds surrounding spaces to aiTargets vector
				aiSearch();
				searching=false;
			}
			if(AItargetsX.empty() && AItargetsY.empty())
			{
				searching = false;
			}

		}
	}

}
//(Mjarvis1997) changed function type to string, so it can return the results of the hit, added currentPlayer parameter
//added all the if statements to update the board based on the check
string Game::checkHit(int loc1, int loc2, bool isP1)//(Mjarvis1997) determines if the chosen location is a hit/miss or has been already chosen
{
	//used by fire method
	if (isP1)
	{
		if (p2->getBoardValue(loc1, loc2) == 0)//hit water
		{
			p2->updateBoard(loc1, loc2, 2, 0);//marks missed ship with value of 2
			return "miss";

		}
		if (p2->getBoardValue(loc1, loc2) == 1)//already hit ship here
		{
			return "already hit";
		}
		if (p2->getBoardValue(loc1, loc2) == 2)//already missed here
		{
			return "already miss";
		}
		if (p2->getBoardValue(loc1, loc2) >= 5)//hit a ship
		{
			p2->updateBoard(loc1, loc2, 1, p2->getBoardValue(loc1, loc2));//marks hit ship with value of 1
			return "hit";
		}
	}
	else
	{
		if (p1->getBoardValue(loc1, loc2) == 0)//hit water
		{
			p1->updateBoard(loc1, loc2, 2, 0);//marks missed ship with value of 2
			return "miss";

		}
		if (p1->getBoardValue(loc1, loc2) == 1)//already hit ship here
		{
			return "already hit";
		}
		if (p1->getBoardValue(loc1, loc2) == 2)//already missed here
		{
			return "already miss";
		}
		if (p1->getBoardValue(loc1, loc2) >= 5)//hit a ship
		{
			p1->updateBoard(loc1, loc2, 1, p1->getBoardValue(loc1, loc2));//marks hit ship with value of 1
			return "hit";
		}
	}
	return "error bool isP1 not assigned properly";
}



//uses set method in player class modifyShips((int x, int y, string orientation, int shipType)
//if parameter "player" is true, then player 1's board is being modified
//otherwise if "player" is false, then player 2's board is being modified
//assumes that player is inputting anchorpoints (x,y) in form "x y". Does not assume valid input
void Game::placeShips(bool player, bool isTwoPlayers)
{
	int anchorPointX;
	int anchorPointY;
	int shipsPlacedCounter = 0;
	string orientation;
	bool validPlacement = false;
	int temp;

	if(isTwoPlayers)
	{
		if (player)
		{
			cout<<"Player 1, please place your ship."<<endl;
			while (shipsPlacedCounter < 5)
			{
				validPlacement = false;
				printBoard(true);
				while (!validPlacement)
				{
					cout << "Place your ship of length " << p1->getPlayerShips(shipsPlacedCounter) << ". What are the x and y coordinates? " << endl;
					cin >> anchorPointX >> anchorPointY;
					while(cin.fail())
					{
						cin.clear();
						cin.ignore(256,'\n');
						cout<<"Please only input whole numbers for both x and y coordinates."<<endl;
						cin >> anchorPointX >> anchorPointY;
					}
					cout << "What is the orientation of the ship? (up, down, left, right, lower case only)" << endl;
					cin >> orientation;
					validPlacement = p1->modifyShips(anchorPointX, anchorPointY, orientation, p1->getPlayerShipTypes(shipsPlacedCounter), false);
				}
				shipsPlacedCounter++;
			}
		}
		else
		{
			cout<<"Player 2, please place your ship."<<endl;
			while (shipsPlacedCounter < 5)
			{
				validPlacement = false;
				printBoard(false);
				while (!validPlacement)
				{
					cout << "Place your ship of length " << p2->getPlayerShips(shipsPlacedCounter) << ". What are the x and y coordinates? " << endl;
					cin >> anchorPointX >> anchorPointY;
					while(cin.fail())
					{
						cin.clear();
						cin.ignore(256,'\n');
						cout<<"Please only input whole numbers for both x and y coordinates."<<endl;
						cin >> anchorPointX >> anchorPointY;
					}
					cout << "What is the orientation of the ship? (up, down, left, right, lower case only)" << endl;
					cin >> orientation;
					validPlacement = p2->modifyShips(anchorPointX, anchorPointY, orientation, p2->getPlayerShipTypes(shipsPlacedCounter), false);
				}
				shipsPlacedCounter++;
			}
		}
	}
	else if(!isTwoPlayers)
	{
		if (player)
		{
			cout<<"Player 1, please place your ship."<<endl;
			while (shipsPlacedCounter < 5)
			{
				validPlacement = false;
				printBoard(true);
				while (!validPlacement)
				{
					cout << "Place your ship of length " << p1->getPlayerShips(shipsPlacedCounter) << ". What are the x and y coordinates? " << endl;
					cin >> anchorPointX >> anchorPointY;
					while(cin.fail())
					{
						cin.clear();
						cin.ignore(256,'\n');
						cout<<"Please only input whole numbers for both x and y coordinates."<<endl;
						cin >> anchorPointX >> anchorPointY;
					};
					cout << "What is the orientation of the ship? (up, down, left, right, lower case only)" << endl;
					cin >> orientation;
					validPlacement = p1->modifyShips(anchorPointX, anchorPointY, orientation, p1->getPlayerShipTypes(shipsPlacedCounter), false);
				}
				shipsPlacedCounter++;
			}
		}
		else
		{
			while(shipsPlacedCounter < 5)
			{
				validPlacement = false;
				while(!validPlacement)
				{
					srand (time(NULL));
					anchorPointX = rand() % 10 + 1;
					srand (time(NULL));
					anchorPointY = rand() % 10 + 1;
					srand (time(NULL));
					temp = rand() % 4;
					switch(temp)
					{
						case 0: orientation = "up";
						break;
						case 1: orientation = "down";
						break;
						case 2: orientation = "left";
						break;
						case 3: orientation = "right";
						break;
					}
					validPlacement = p2->modifyShips(anchorPointX, anchorPointY, orientation, p2->getPlayerShipTypes(shipsPlacedCounter), true);
				}
				shipsPlacedCounter++;
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

	if (input.size() > 1)
	{
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
	cout << "\033[1;32mPlayer 1's turn!\033[0m" << endl;
	else
	cout << "\033[1;34mPlayer 2's turn!\033[0m" << endl;

	if(isTwoPlayers)
	{
		cout << "Input any key when ready!" << endl;
		string x;
		cin >> x;//maybe make not sucky

		printBoard(isP1);

		fire(isP1);
	}
	//else for a.i.
	else
	{
		cout << "Input any key when ready!" << endl;
		string x;
		cin >> x;//maybe make not sucky

		printBoard(isP1);

		fire(isP1);

	}
}

void Game::gControl() //true = p1
{
	bool playerBool = true;

	//some ship place method here
	//for 2players
	if(isTwoPlayers)
	{
		placeShips(true,true);
		placeShips(false,true);
	}
	//vs AI
	else
	{
		placeShips(true,false);
		placeShips(false,false);
	}

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

void Game::aiSearch()
{
	int x = AIhit [0];
	int y = AIhit [1];
	if (x+1<11 && x+1>0)
	{
		if(p1 ->getBoardValue(x+1,y) == 0 || p1 ->getBoardValue(x+1,y))
		{
			AItargetsX.push_back(x+1);
			AItargetsY.push_back(y);
		}
	}
	if (x-1<11 && x-1>0)
	{
		if(p1 ->getBoardValue(x-1,y) == 0 || p1 ->getBoardValue(x-1,y) >= 5)
		{
			AItargetsX.push_back(x-1);
			AItargetsY.push_back(y);
		}
	}
	if (y+1<11 && y+1>0)
	{
		if(p1 ->getBoardValue(x,y+1) == 0 || p1 ->getBoardValue(x,y+1) >= 5)
		{
			AItargetsX.push_back(x);
			AItargetsY.push_back(y+1);
		}
	}
	if (y-1<11 && y-1>0)
	{
		if(p1 ->getBoardValue(x,y-1) == 0 || p1 ->getBoardValue(x,y-1) >= 5)
		{
			AItargetsX.push_back(x);
			AItargetsY.push_back(y-1);
		}
	}
}
