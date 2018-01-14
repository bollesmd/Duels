//Game specific functions: For application affected functionality

#include "stdafx.h"
#include "functions.h"

using namespace std;

//Draw Menu
void DrawTitle(bool newGame)
{
	system("cls");

	//draw game title header
	cout << "=================================================" << endl
		<< "=================================================" << endl
		<< "==    DDDDD   UU  UU  EEEEEE  LL       SSSS    ==" << endl
		<< "==    DD  DD  UU  UU  EE      LL      SS       ==" << endl
		<< "==    DD  DD  UU  UU  EEEE    LL       SSS     ==" << endl
		<< "==    DD  DD  UU  UU  EE      LL         SS    ==" << endl
		<< "==    DDDDD    UUUU   EEEEEE  LLLLLL  SSSS     ==" << endl
		<< "=================================================" << endl
		<< "=================================================" << endl << endl;

	if (newGame)
	{
		cout << "=======Welcome players! Let's get bloody!!=======" << endl << endl;
		system("Pause");
		system("cls");
	}
}

//Confirmation of player selections
char ValidateUserSelection(char select, string s)
{
	bool validated = false;
	select = tolower(select);

	while (!validated)
	{
		//check selection validity
		if (s == "ABC")
		{
			switch (select)
			{
			case 'a':
			case 'b':
			case 'c':
				validated = true;
				break;

			default:
				cout << "Invalid selection, please re-enter." << endl;
				cout << "Valid choices: a, b, c" << endl;
				cin >> select;
				continue;
			}
		}
		else if (s == "ABCI")
		{
			switch (select)
			{
			case 'a':
			case 'b':
			case 'c':
			case 'i':
				validated = true;
				break;
			default:
				cout << "Invalid selection, please re-enter.";
				cout << "Valid choices: a, b, c, i" << endl;
				cin >> select;
				continue;
			}
		}
		else if (s == "ABCDE")
		{
			switch (select)
			{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
				validated = true;
				break;
			default:
				cout << "Invalid selection, please re-enter.";
				cout << "Valid choices: a, b, c, d, e" << endl;
				cin >> select;
				continue;
			}
		}
	}

	return select;
}

