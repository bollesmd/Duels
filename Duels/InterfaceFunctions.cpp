#include<iostream>
#include<string>

#include "stdafx.h"
#include "functions.h"

using namespace std;

//Confirmation of player selections
char selectCheck(char select, int s1)
{
	//check selection validity
	if (s1 == 1)		//checks and runs for "abc" inputs
	{
		while (select != 'a' && select != 'b' && select != 'c')
		{
			switch (select)
			{
			case 'A':
				select = 'a';
				break;
			case 'B':
				select = 'b';
				break;
			case 'C':
				select = 'c';
				break;
			default:
				cout << "Invalid selection, please re-enter.";
				cin >> select;
				continue;
			}
		}
	}
	else if (s1 == 2)		//checks and runs for "abci" inputs
	{
		while (select != 'a' && select != 'b' && select != 'c' && select != 'i')
		{
			switch (select)
			{
			case 'A':
				select = 'a';
				break;
			case 'B':
				select = 'b';
				break;
			case 'C':
				select = 'c';
				break;
			case 'I':
				select = 'i';
				break;
			default:
				cout << "Invalid selection, please re-enter.";
				cin >> select;
				continue;
			}
		}
	}
	else		//runs for all remaining menu selection entries
	{
		while (select != 'a' && (select != 'b' && (select != 'c' && (select != 'd' && select != 'e'))))
		{
			switch (select)
			{
			case 'A':
				select = 'a';
				break;
			case 'B':
				select = 'b';
				break;
			case 'C':
				select = 'c';
				break;
			case 'D':
				select = 'd';
				break;
			case 'E':
				select = 'e';
				break;
			default:
				cout << "Invalid selection, please re-enter.";
				cin >> select;
				continue;
			}
		}
	}
	return select;
}