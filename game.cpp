#include "game.h"


game::game()//initiates game by deterimining # of players, and creating player objects accordingly
{
	string temp;
	

	cout << "Make a new game" << endl;
	cout << "1 or 2 players" << endl;
	//add code for that here

	cin >> temp;//(MJarvis1997) Added input to establish the # of players with bool isTwoPlayers
	if (temp == "1")
	{
		isTwoPlayers = false;
	}
	if (temp == "2")
	{
		isTwoPlayers = true;
	}
	temp = "";

	makePlayers(isTwoPlayers);


}

//deconstructor?

void game::printBoard(bool isP1)
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

void game::fire(bool isP1)//determines coordinates of fire position(whether from a realPlayer or an AI) and then uses checkHit and updateBoard to make the according changes
						  //(Mjarvis1997) added bool parameter so that game.fire can be used for both real and computer players
{
	
	if (isP1)//(Mjarvis1997) fires for first player
	{
		int temp;//(Mjarvis1997)changed to int from string to accomodate intArray[][] normal form
		int temp2;

		cout << "Please select x" << endl;
		cin >> temp;
		cout << "Please select y" << endl;
		cin >> temp2;
		checkHit(temp, temp2, isP1);
		
			//cout << cleanInput(temp, 10) << endl; //10 is max int allowed
			//cout << cleanInput(temp2, 10) << endl;
	}
	if ((!isP1) && isTwoPlayers)//(Mjarvis1997) fires for real second player
	{
		int temp;
		int temp2;

		cout << "Please select x" << endl;
		cin >> temp;
		cout << "Please select y" << endl;
		cin >> temp2;
		checkHit(temp, temp2, isP1);
	}
	else
	{
		// algorith for AI firing

	}

}
//(Mjarvis1997) changed function type to string, so it can return the results of the hit, added currentPlayer parameter
//added all the if statements to update the board based on the check
string game::checkHit(int loc1, int loc2, bool isP1)//(Mjarvis1997) determines if the chosen location is a hit/miss or has been already chosen
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
void game::placeShips()
{

}


void game::makePlayers(bool isTwoPlayers)//(Mjarvis1997)changed pType to isTwoPlayers
{
	//for making comp player
	//(Mjarvis1997) moved this here from game function to consolidate all the player creation to this makePlayer function
	if (isTwoPlayers) // 2 players, else is 1 and comp
	{
		string temp;
		cout << "Player 1 enter name:" << endl;
		cin >> temp;
		p1 = new player(temp);

		temp = "";

		cout << "Player 2 enter name:" << endl;
		cin >> temp;
		p2 = new player(temp);
	}
	else//(MJarvis1997)Filled in this else statement to create 1 player of inputted name, and also to create an AI player object
	{
		string temp;
		cout << "Player 1 enter name:" << endl;
		cin >> temp;
		p1 = new player(temp);

		temp = "";

		cout << "A 'BattleBot' has been created for you to test your skills against!";
			p2 = new player("BattleBot");
	}

}

//everytime taking in cord info as string
int game::cleanInput(string input, int range)
{
	int t1;
	int t2;

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
void game::gRound(bool isP1) //true = p1
{
	//game turn logic.
}


