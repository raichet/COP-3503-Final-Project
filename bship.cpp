

#include "game.h"

using namespace std;

int main() 
{
	Game* g1;
	bool playAgain;
	string choice;

	
	do
	{
		g1 = new gGame();
		g1->gControl;
		cout << "Would you like to play again? (y/n)" << endl;
		cin >> choice;
		while ( playAgain != null)
		{
			if (choice == "y")
			{
				playAgain = true;
			}
			else if (choice =="n")
			{
				playAgain = false;
			}
			else
			{
				cout << "Unreadable input. Please try again... " << endl;
				cin >> choice;
			}
		}
	delete g1;
	} whlie (playAgain == true); 
	
	
	return 0;
}
