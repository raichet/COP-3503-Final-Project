

#include "game.h"

using namespace std;

int main() 
{
	Game* g1;
	bool playAgain;
	string choice;

	//system("/e[0;34m")
	
	do
	{
		g1 = new Game();
		g1->gControl();
		cout << "Would you like to play again? (y/n)" << endl;
		cin >> choice;
		
		while (choice != "y" && choice != "n")
		{

			cout << "Unreadable input. Please try again... " << endl;
			cin >> choice;
			
		}
		
		if (choice == "y")
		{
			playAgain = true;
		}
		if (choice =="n")
		{
			playAgain = false;
		}
		
	delete g1;
	} while (playAgain == true); 
	
	
	return 0;
}
