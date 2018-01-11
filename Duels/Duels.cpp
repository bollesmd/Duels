//Michael Bolles
//Created VS2010: 1/10/13 
//Edited for VS1027: 1/1/18

//Final Project CSPG106: My first student C++ programming project 
// Duels.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <iomanip>
#include <fstream>

#include "functions.h"

using namespace std;

void main()		
{
	//declaring player variables
	string pOne, pTwo, fileName, p1Class, p1Wpn, p1Armor, p2Class, p2Wpn, p2Armor;

	int p1Winner = 0, p2Winner = 0, p1Score = 0, p2Score = 0, 
		coin = 0, i, x, q, s1, pCounter1 = 0, pCounter2 = 0, timer = NULL,
		//inventory item menu
		hPotion1 = 2, hPotion2 = 2, mPotion1 = 2, mPotion2 = 2, pPotion1 = 2, pPotion2 = 2;
	
	//variable arrays for player stats and boosts: 
	//Boosts: 0=AttkBoost, 1=MagicBoost, 2=HealthBoost, 3=Hit%, 4=Critical%
	int p1Boost[5] = { 0,0,0,0,0 };      
	int p2Boost[5] = { 0,0,0,0,0 };  
	bool p1StatBoosts[5] = { true, true, true, true, true };
	bool p2StatBoosts[5] = { true, true, true, true, true };
	//Stats: 0=Physical Hit%, 1=Attack Damage, 2=Magic Damage, 3=Special Damage, 4=Critical %, 5=PhysicalDefense, 6=MagicDefense, 7=total wins, 8=games played
	double p1Stats[14] = { 0,0,0,0,0,0,0,0,0 };
	double p2Stats[14] = { 0,0,0,0,0,0,0,0,0 };

	double damage;
			
	//player stat variables
	double p1Health, p1Special, p1Magic;
	double p2Health, p2Special, p2Magic;

	char playGame, selection, pH = 'z', saveChar;
	bool game = true, charSelect = true, turns = true, p1Turn = true, p2Turn = true, pickHealth = true, 
			play = true, p1Poison = false, p2Poison = false;
	time_t start, end;

	//fstream variables for load/save files
	ifstream inFileA, inFileB;
	ofstream outFileA, outFileB;

	string pClass[3] = { "Barbarian", "Mage", "Rogue" };
	string Wpn[9] = { "Long Sword", "Axe", "Mace", "Wand", "Staff", "Enchanted Sword", "Dagger", "Bow", "Short Sword" };
	string armorType[3] = { "Light", "Heavy", "Magical" };
	string statBoosts[5] = { "A - +1 Attack Damage", "B - +1 Magic Damage", "C - +5 Health Points", "D - +5 Hit Percentage", "E - +5 Critical Percentage" };
	
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
	cout << "=======Welcome players! Let's get bloody!!=======" << endl << endl;

	//Initialize player save files
	while (p1Turn)		//player one enters character name and loads stats if available
	{
		cout << "Player one, do you have a saved character? (y) or (n) ";
		cin >> selection;		//user inputs choice
		cin.ignore(1000, '\n');
		cout << endl;

		if (selection == 'y' || selection == 'Y')		//check against user entry
		{
			cout << "What's your character's name? ";		//requests player one's name
			getline(cin, pOne);		//user enters name
			cout << endl << "Please verify name: " << pOne << " is correct. (y) or (n) ";		//checks that name was input correctly
			cin >> selection;		//user confirms name entry
			cin.ignore(1000, '\n');

			if (selection == 'y' || selection == 'Y')		//if user enters yes name is correct
			{
				inFileA.open(pOne + ".txt");		//opens filename given by user
				if (!inFileA)		//checks user's filename is invalid/available
				{
					cout << pOne << ": that saved character doesn't exist, starting from scratch!!" << endl;		//if file doesn't exist requests entry of new file from user
				}
				else		//runs if user enters an existing filename
				{
					cout << "Thank you " << pOne << ", loading player stats." << endl;		//displays message confirming file load
					inFileA >> pOne;

					//load player stats into Player Boost array
					for (int i = 0; i < 5; i++)
					{
						inFileA >> p1Boost[i];
					}
					
					for (i = 0; i < 9; i++)
					{
						inFileA >> p1Stats[i];
					}
				}

				inFileA.close();
				p1Turn = false;
				system("Pause");
				system("cls");
			}
			else
				cout << "Please retry." << endl;		//requests new entry if name is entered incorrectly
		}
		else
		{
			//if no character exists for player, start a new one
			cout << "Please enter a new character name: ";		
			getline(cin, pOne);
			cout << "Please verify name: " << pOne << " is correct. (y) or (n) ";
			cin >> selection;
			cin.ignore(1000, '\n');

			if (selection == 'y' || selection == 'Y')
			{
				outFileA.open(pOne + ".txt");		//creates save file for player
				outFileA.close();
				p1Turn = false;
				system("cls");
			}
		}
	}

	while (p2Turn)		//player two enters name and loads stats if available
	{
		cout << "Player two, do you have a saved character? (y) or (n) ";
		cin >> selection;
		cin.ignore(1000, '\n');
		cout << endl;

		if (selection == 'y' || selection == 'Y')
		{
			cout << "What's your character's name? ";		//user enters character name
			getline(cin, pTwo);
			cout << endl << "Please verify name: " << pTwo << " is correct. (y) or (n) ";
			cin >> selection;
			cin.ignore(1000, '\n');

			if (selection == 'y' || selection == 'Y')		//checks if entry is correct and runs load stats if yes
			{
				inFileB.open(pTwo + ".txt");

				if (!inFileB)
					cout << "Player one that file doesn't exist, start from scratch!";		//if file not found, offers to create file
				else
				{
					cout << "Thank you " << pTwo << ", loading player stats." << endl;		//if file found loads player's stats
					for (int i = 0; i<5; i++)
						inFileB >> p2Boost[i];
					//inFileB >> "\n";
					for (i = 0; i<9; i++)
						inFileB >> p2Stats[i];
				}

				inFileB.close();
				p2Turn = false;
				system("Pause");
				system("cls");
			}
			else
				cout << "Please retry." << endl;		//requests new entry if name is entered incorrectly
		}
		else
		{
			cout << "Please enter a new character name: ";		//if no character exists for player, starts new one
			getline(cin, pTwo);
			cout << "Please verify name: " << pTwo << " is correct. (y) or (n) ";
			cin >> selection;
			cin.ignore(1000, '\n');
			if (selection == 'y' || selection == 'Y')
			{
				outFileB.open(pTwo + ".txt");		//creates save file for player
				outFileB.close();
				p2Turn = false;
				system("cls");
			}
		}
	}

	while (game)		//game loop
	{
		while (pickHealth)		//health selection loop runs only once a session to determine player starting health unless otherwise indicated at end of game
		{
			cout << "Select Player Health Settings." << endl		//User selects player health level
				<< "A - Low: 50%" << endl << "B - Normal: 100%" << endl << "C - High: 250%" << endl << "Selection: ";
			cin >> selection;
			cin.ignore(1000, '\n');
			s1 = 1;
			selection = selectCheck(selection, s1);		//check selection function
			pH = selection;		//sets variable to selection for later use
			pickHealth = false;		//stops loop unless user requests new entry of health settings
		}

		//set who goes first
		if (p1Winner == 1)		
		{
			cout << pOne << " goes first." << endl;
			p1Turn = true;		//true if p1 turn
			p1Winner = 0;
		}
		else if (p2Winner == 1)
		{
			cout << pTwo << " goes first." << endl;
			p2Turn = true;		//true if p2 turn
			p2Winner = 0;
		}
		else		//checks who goes first and runs if there was no winner
		{
			int pGuess;
			char coinToss;

			//requests player one to guess heads or tails
			cout << "Player one, guess heads (h) or tails (t): ";
			time(&start);		//starts timer
			cin >> coinToss;		//user guesses heads or tails
			time(&end);		//stops timer
			cin.ignore(1000, '\n');

			while (coinToss != 'h' && coinToss != 't')
			{
				switch (coinToss)		//checks h/t guess is formatted correctly
				{
				case 'H':
					coinToss = 'h';
					break;
				case 'T':
					coinToss = 't';
					break;
				default:
					cout << "Incorrect entry, please re-enter";
					cin >> coinToss;
					continue;
				}
			}

			if (coinToss == 'h')		//sets player entry to numeral equivalent
				pGuess = 1;
			else if (coinToss == 't')
				pGuess = 0;

			timer = difftime(end, start);		//sets timer to user entry based time
			srand(timer);		//seed random number with time 
			coin = rand() % 2;		//creates a random number 0 or 1

			if (coin == 1)
				cout << "HEADS" << endl;
			else
				cout << "TAILS" << endl;

			if (pGuess == coin)
			{
				cout << "Your guessed right player one, you go first." << endl << endl;		//if player guessed correctly sets p1 to go first
				p1Turn = true;
			}
			else
			{
				cout << "You guessed wrong player one, player two goes first." << endl << endl;		//if player guessed incorrectly, sets p2 goes first
				p2Turn = true;
			}
		}

		//Player health stat reset function
		playerStatus(p1Health, p2Health, p1Magic, p2Magic, p1Special, p2Special, hPotion1, mPotion1, pPotion1, 
								hPotion2, mPotion2, pPotion2, pH);		

		i = 0;

		while (charSelect)		//apply arrays for character avatar, wpns, and armor
		{
			while (p1Turn)		//sets player one stat bases
			{
				cout << pOne << " pick your character:" << endl;
				cout << "A - Barbarian" << endl
					<< "B - Mage" << endl
					<< "C - Rogue" << endl << "selection: ";
				cin >> selection;
				cin.ignore(1000, '\n');
				cout << endl;
				s1 = 1;
				selectCheck(selection, s1);

				if (selection == 'a')
				{
					//set player stats to barb basic
					p1Class = pClass[0];
					p1Stats[0] = 60;		//physical hit%
					p1Stats[1] = 20;		//attack damage
					p1Stats[2] = 10;		//magic damage
					p1Stats[3] = 25;		//special damage
					p1Stats[4] = 20;		//critical hit%

					cout << pOne << " pick your weapon:" << endl		//displays menu for weapon choice
						<< "A - Long Sword" << endl
						<< "B - Axe" << endl
						<< "C - Mace" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//check selections function

					switch (selection)
					{
					case 'a':		//set player wpn stats to LongSword
					{
						p1Wpn = Wpn[0];		//sets player weapon
						p1Stats[0] += 0;		//physical hit%
						p1Stats[1] += 5;		//attack damage
						p1Stats[2] += 5;		//magic damage
					}
					break;
					case 'b':		//set player wpn stats to Axe
					{
						p1Wpn = Wpn[1];
						p1Stats[0] -= 5;
						p1Stats[1] += 10;
						p1Stats[2] += 0;
					}
					break;
					case 'c':		//set player wpn stats to Mace
					{
						p1Wpn = Wpn[2];
						p1Stats[0] += 5;
						p1Stats[1] += 0;
						p1Stats[2] += 10;
					}
					break;
					}
				}
				else if (selection == 'b')
				{
					//set player stats to mage basic
					p1Class = pClass[1];
					p1Stats[0] = 50;		//physical hit%
					p1Stats[1] = 10;		//attack damage
					p1Stats[2] = 20;		//magic damage
					p1Stats[3] = 25;		//special damage
					p1Stats[4] = 20;		//critical hit%

					cout << pOne << " pick your weapon:" << endl		//displays mage's weapon selection
						<< "A - Wand" << endl
						<< "B - Staff" << endl
						<< "C - Enchanted Sword" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//selection check function

					if (selection == 'a')
					{
						//set player wpn stats to Wand
						p1Wpn = Wpn[3];
						p1Stats[0] += 10;		//physical hit%
						p1Stats[1] -= 5;		//attack damage
						p1Stats[2] += 10;		//magic damage
					}
					else if (selection == 'b')
					{
						//set player wpn stats to Staff
						p1Wpn = Wpn[4];
						p1Stats[0] += 0;
						p1Stats[1] += 0;
						p1Stats[2] += 5;
					}
					else
					{
						//set player wpn stats to enchSword
						p1Wpn = Wpn[5];
						p1Stats[0] -= 10;
						p1Stats[1] += 5;
						p1Stats[2] += 0;
					}
				}
				else
				{
					//set player stats to rogue basic
					p1Class = pClass[2];
					p1Stats[0] = 70;		//physical hit%
					p1Stats[1] = 15;		//attack damage
					p1Stats[2] = 15;		//magic damage
					p1Stats[3] = 15;		//special damage
					p1Stats[4] = 20;		//critical hit%

					cout << pOne << " pick your weapon:" << endl		//requests input of weapon
						<< "A - Dagger" << endl
						<< "B - Bow" << endl
						<< "C - Short Sword" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//selection check function

					if (selection == 'a')
					{
						//set player wpn stats to Dagger
						p1Wpn = Wpn[6];
						p1Stats[0] += 10;		//physical hit%
						p1Stats[1] -= 5;		//attack damage
						p1Stats[2] += 10;		//magic damage
					}
					else if (selection == 'b')
					{
						//set player wpn stats to Bow
						p1Wpn = Wpn[7];
						p1Stats[0] += 0;
						p1Stats[1] += 0;
						p1Stats[2] += 5;
					}
					else
					{
						//set player wpn stats to ShortSword
						p1Wpn = Wpn[8];
						p1Stats[0] -= 10;
						p1Stats[1] += 5;
						p1Stats[2] += 0;
					}
				}
				cout << pOne << " pick your armor type:" << endl		//displays menu and requests input of armor type
					<< "A - Light" << endl
					<< "B - Heavy" << endl
					<< "C - Magical" << endl;
				cin >> selection;
				cin.ignore(1000, '\n');
				cout << endl;
				selectCheck(selection, s1);		//selection check function

				if (selection == 'a')
				{
					//set player armor to Light
					p1Armor = armorType[0];
					p1Stats[5] = 25;
					p1Stats[6] = 25;
				}
				else if (selection == 'b')
				{
					//set player armor to heavy
					p1Armor = armorType[1];
					p1Stats[5] = 50;
					p1Stats[6] = 10;
				}
				else
				{
					//set player armor to magic
					p1Armor = armorType[2];
					p1Stats[5] = 10;
					p1Stats[6] = 50;
				}

				p1Turn = false;
				p2Turn = true;

				system("cls");

				if (i < 1)
					i++;
				else
				{
					charSelect = false;
					break;
				}
			}

			while (p2Turn)		//sets player two's stat bases
			{
				cout << pTwo << " pick your character:" << endl;
				cout << "A - Barbarian" << endl
					<< "B - Mage" << endl
					<< "C - Rogue" << endl << "selection: ";
				cin >> selection;
				cin.ignore(1000, '\n');
				cout << endl;
				s1 = 1;
				selectCheck(selection, s1);		//calls select check function

				if (selection == 'a')
				{
					//set player stats to barb basic
					p2Class = pClass[0];
					p2Stats[0] = 60;
					p2Stats[1] = 20;
					p2Stats[2] = 10;
					p2Stats[3] = 25;
					p2Stats[4] = 20;

					cout << pTwo << " pick your weapon:" << endl
						<< "A - Long Sword" << endl
						<< "B - Axe" << endl
						<< "C - Mace" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//calls select check function

					if (selection == 'a')
					{
						//set player wpn stats to LongSword
						p2Wpn = Wpn[0];
						p2Stats[0] += 0;
						p2Stats[1] += 5;
						p2Stats[2] += 5;
					}
					else if (selection == 'b')
					{
						//set player wpn stats to Axe
						p2Wpn = Wpn[1];
						p2Stats[0] -= 5;
						p2Stats[1] += 10;
						p2Stats[2] += 0;
					}
					else
					{
						//set player wpn stats to Mace
						p2Wpn = Wpn[2];
						p2Stats[0] += 5;
						p2Stats[1] += 0;
						p2Stats[2] += 10;
					}
				}
				else if (selection == 'b')
				{
					//set player stats to mage basic
					p2Class = pClass[1];
					p2Stats[0] = 50;
					p2Stats[1] = 10;
					p2Stats[2] = 20;
					p2Stats[3] = 25;
					p2Stats[4] = 20;

					cout << pTwo << " pick your weapon:" << endl
						<< "A - Wand" << endl
						<< "B - Staff" << endl
						<< "C - Enchanted Sword" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//calls select check function

					if (selection == 'a')
					{
						//set player wpn stats to Wand
						p2Wpn = Wpn[3];
						p2Stats[0] += 10;
						p2Stats[1] -= 5;
						p2Stats[2] += 10;
					}
					else if (selection == 'b')
					{
						//set player wpn stats to Staff
						p2Wpn = Wpn[4];
						p2Stats[0] += 0;
						p2Stats[1] += 0;
						p2Stats[2] += 5;
					}
					else
					{
						//set player wpn stats to enchSword
						p2Wpn = Wpn[5];
						p2Stats[0] -= 10;
						p2Stats[1] += 5;
						p2Stats[2] += 0;
					}
				}
				else
				{
					//set player stats to rogue basic
					p2Class = pClass[2];
					p2Stats[0] = 70;
					p2Stats[1] = 15;
					p2Stats[2] = 15;
					p2Stats[3] = 15;
					p2Stats[4] = 20;

					cout << pTwo << " pick your weapon:" << endl
						<< "A - Dagger" << endl
						<< "B - Bow" << endl
						<< "C - Short Sword" << endl;
					cin >> selection;
					cin.ignore(1000, '\n');
					cout << endl;
					selectCheck(selection, s1);		//calls select check function

					if (selection == 'a')
					{
						//set player wpn stats to Dagger
						p2Wpn = Wpn[6];
						p2Stats[0] += 10;
						p2Stats[1] -= 5;
						p2Stats[2] += 10;
					}
					else if (selection == 'b')
					{
						//set player wpn stats to Bow
						p2Wpn = Wpn[7];
						p2Stats[0] += 0;
						p2Stats[1] += 0;
						p2Stats[2] += 5;
					}
					else
					{
						//set player wpn stats to ShortSword
						p2Wpn = Wpn[8];
						p2Stats[0] -= 10;
						p2Stats[1] += 5;
						p2Stats[2] += 0;
					}
				}

				cout << pTwo << " pick your armor type:" << endl
					<< "A - Light" << endl
					<< "B - Heavy" << endl
					<< "C - Magical" << endl;
				cin >> selection;
				cin.ignore(1000, '\n');
				cout << endl;
				selectCheck(selection, s1);		//calls select check function

				if (selection == 'a')
				{
					//set player armor to Light
					p2Armor = armorType[0];
					p2Stats[5] = 25;
					p2Stats[6] = 25;
				}
				else if (selection == 'b')
				{
					//set player armor to heavy
					p2Armor = armorType[1];
					p2Stats[5] = 50;
					p2Stats[6] = 10;
				}
				else
				{
					//set player armor to magic
					p2Armor = armorType[2];
					p2Stats[5] = 10;
					p2Stats[6] = 50;
				}

				p1Turn = true;
				p2Turn = false;

				system("cls");
			}

			if (i < 1)
				i++;
			else
			{
				charSelect = false;
				break; 
			}
		}

		while (play)
		{
			playerStatus(p1Health, p2Health, p1Magic, p2Magic, p1Special, p2Special, hPotion1, mPotion1, pPotion1, hPotion2, mPotion2, pPotion2, pH);		//function called to reset player status

			//adds boosts to base stats for player one																																				//implement stat boosts for player 1
			p1Health += p1Boost[2];		
			p1Stats[0] += p1Boost[3];
			p1Stats[1] += p1Boost[0];
			p1Stats[2] += p1Boost[1];
			p1Stats[4] += p1Boost[4];

			//check that player's stat boosts and limits player's growth
			if (p1Health > 250)		
			{
				p1Health = 250;
				p1StatBoosts[0] = false;
			}
			if (p1Stats[0] > 100)
			{
				p1Stats[0] = 100;
				p1StatBoosts[1] = false;
			}
			if (p1Stats[1] > 40)
			{
				p1Stats[1] = 40;
				p1StatBoosts[2] = false;
			}
			if (p1Stats[2] > 35)
			{
				p1Stats[2] = 35;
				p1StatBoosts[3] = false;
			}
			if (p1Stats[4] > 50)
			{
				p1Stats[4] = 50;
				p1StatBoosts[4] = false;
			}

			//implement stat boosts for player 2
			p2Health += p2Boost[2];
			p2Stats[0] += p2Boost[3];
			p2Stats[1] += p2Boost[0];
			p2Stats[2] += p2Boost[1];
			p2Stats[4] += p2Boost[4];

			if (p2Health > 250)
			{
				p2Health = 250;
				p2StatBoosts[0] = false;
			}
			if (p2Stats[0] > 100)
			{
				p2Stats[0] = 100;
				p2StatBoosts[1] = false;
			}
			if (p2Stats[1] > 40)
			{
				p2Stats[1] = 40;
				p2StatBoosts[2] = false;
			}
			if (p2Stats[2] > 35)
			{
				p2Stats[2] = 35;
				p2StatBoosts[3] = false;
			}
			if (p2Stats[4] > 50)
			{
				p2Stats[4] = 50;
				p2StatBoosts[4] = false;
			}

			while (turns)		//turn loops
			{
				while (p1Turn && p1Health > 0)		//Player one's turn 
				{
					system("cls");
					cout << pOne << " Status;" << endl
						<< "Health: " << p1Health << " points" << endl		//outputs player 1 health
						<< "Bar: ";  
					i = 0;
					while (i < p1Health)		//outputs visual health bar
					{
						cout << "X";
						i++;
					}
					cout << endl;
					cout << "Mana: " << p1Magic << " points" << endl;		//outputs mana
					cout << "Stamina: " << p1Special << " points" << endl << endl;		//outputs stamina

					cout << pTwo << " Health: " << p2Health << " points" << endl		//outputs opponents health bar
						<< "Bar: ";
					i = 0;
					while (i < p2Health)
					{
						cout << "O";
						i++;
					}
					cout << endl << endl;

					if (p1Poison)		//checks and runs poison damage if player is poisoned
					{
						cout << pOne << " takes poison damage.";
						p1Health -= 5;
						pCounter1++;		//increments poison counter and stops poison state when 5 is reached
						if (pCounter1 == 5)
						{
							pCounter1 = 0;
							p1Poison = false;
						}
						if (p1Health <= 0)		//exit turn if player health reaches 0
							break;
					}

					cout << pOne << " select your move." << endl;		//player choose between options to attack, defend, spAttk or use item on opponent
					cout << "A - Attack" << endl;
					cout << "B - Magic" << endl;
					cout << "C - Special" << endl;
					cout << "I - Item Menu" << endl << "Selection: ";
					time(&start);
					cin >> selection;
					time(&end);
					cin.ignore(1000, '\n');
					cout << endl;

					s1 = 2;
					selectCheck(selection, s1);		//calls select check function

					if (selection == 'a')		//attack method
					{
						timer = difftime(end, start);
						srand(timer);		//sets random number for attack hit%
						x = rand() % 100 + 1;

						if (x <= p1Stats[0])		//checks hit percentage
						{
							if (x <= 5)		//runs if random number is 5 or less
							{
								cout << "O.o Critical Miss o.O" << endl		//outputs critical miss message
									<< pOne << "takes 5 damage." << endl;
								p1Health -= 5;
							}
							else if (x <= p1Stats[4] && x > 5)		//checks for critical damage
							{
								cout << "*** Critical hit! ***" << endl;		//outputs critical hit message
								damage = p1Stats[1] + (p1Stats[1] / 2);
							}
							else
								damage = p1Stats[1];		//sets damage equal to player 1's stats

							damage = static_cast<int> (damage - (damage * p2Stats[5] / 100));		//sets damage to a whole number based on atatck damage algorithm
							cout << pOne << " hits for " << fixed << setprecision(0) << damage << " points." << endl;
							p2Health -= damage;		//decrements player health based on damage
						}
						else
							cout << pOne << " misses." << endl;		//outputs miss if random number outside of hit% range
					}
					else if (selection == 'b')		//Magic method
					{
						if (p1Magic >= 10)
						{
							damage = p1Stats[2];
							damage = static_cast<int> (damage - (damage * p2Stats[6] / 100));		//sets damage to a whole number based on magic damage algorithm
							cout << pOne << " uses magic for " << damage << " points of damage." << endl;
							p1Magic -= 10;		//decrements player mana
							p2Health -= damage;		//decrements player health based on damage
						}
						else
							cout << pOne << " tries to use magic but doesn't have enough Mana." << endl;		//outputs message if player doesn't have enough mana and ends turn
					}
					else if (selection == 'c')		//Special method
					{
						//Special
						if (p1Special >= 25)
						{
							p1Special -= 25;

							if (p1Class == "Barbarian")		//special for barbarian
							{
								srand(selection);
								x = rand() % 100 + 1;

								if (x <= 75)		//special attack hit% set to 75
								{
									cout << pOne << " uses Bash." << endl;
									damage = static_cast<int> (p1Stats[3] - (p1Stats[3] * p2Stats[6] / 100));		//special attack damage algorithm
									p2Health = p2Health - damage;		//decrements player health based on damage
								}
							}
							else if (p1Class == "Mage")		//special for mage
							{

								cout << pOne << " uses Healing Magic." << endl;		//increments player health by 25
								p1Health += 25;
							}
							else		//special for rogue
							{
								damage = 0;		//sets damage to 0
								q = 0;		//variable for number of hits set to 0
								for (i = 0; i<3; i++)		//runs 3 times for a possible hit each run
								{
									srand(selection);		//sets random number for hits
									x = rand() % 100 + 1;

									if (x <= 50)		//special hit% set to 50
										damage += static_cast<int> (p1Stats[1] - (p1Stats[1] * p2Stats[6] / 100));		//damage algorithm
									p2Health -= damage;		//decrements player health
									q++;		//increments hit counter
								}
								if (q>0)
								{
									cout << pOne << " uses Quick Hits" << endl;		//outputs how many times player hits
									cout << q << " hits for " << damage << " damage" << endl;
								}
								else
									cout << pOne << " uses Quick Hit and misses." << endl;		//outputs miss message
							}
						}
						else
							cout << pOne << " tries to use special but doesn't have enough Stamina." << endl;		//outputs message stating player doesn't have enough stamina and ends turn
					}
					else if (selection == 'i')		//Item Menu method
					{
						cout << "Items:" << endl		//outputs menu for items
							<< "A - Health Potion: " << hPotion1 << endl
							<< "B - Mana Potion: " << mPotion1 << endl
							<< "C - Poison: " << pPotion1 << endl;
						cin >> selection;
						cin.ignore(1000, '\n');
						cout << endl;
						s1 = 1;
						selectCheck(selection, s1);		//calls select check function

						if (selection == 'a')		//runs health potion method
						{
							if (hPotion1 > 0)
							{
								cout << pOne << " uses health potion. +25HP" << endl;
								p1Health += 25;
								hPotion1--;
							}
							else
								cout << "Not enough health potions. " << pOne << " looses turn." << endl;
						}
						else if (selection == 'b')		//runs mana potion method
						{
							if (mPotion1 > 0)
							{
								p1Magic += 25;
								mPotion1--;
							}
							else
								cout << "Not enough mana potions. " << pOne << " looses turn." << endl;
						}
						else		//runs poison method
						{
							if (pPotion1 > 0)
							{
								cout << pOne << " uses poison." << endl;
								p2Poison = true;
								pPotion1--;
							}
							else
								cout << "Not enough poison potions. " << pOne << " looses turn." << endl;
						}
					}

					p1Magic += 5;		//refills mana and special at end of turn for
					p1Special += 5;

					system("Pause");
					p1Turn = false;
					p2Turn = true;
				}

				if (p1Health <= 0 || p2Health <= 0)		//checks to see if either player's health reached 0 and exits turn loop
				{
					turns = false;
					break;
				}

				while (p2Turn && p2Health > 0)		//Player two's turn
				{
					system("cls");
					cout << pTwo << " Status;" << endl
						<< "Health: " << p2Health << " points" << endl		//outputs player 1 health
						<< "Bar: ";
					i = 0;
					while (i < p2Health)		//displays player health bar
					{
						cout << "O";
						i++;
					}
					cout << endl;
					cout << "Mana: " << p2Magic << " points" << endl;		//displays player 2 mana
					cout << "Stamina: " << p2Special << " points" << endl << endl;		//displays player 2 special points

					cout << pOne << " Health: " << p1Health << " points" << endl		//displays opponent health bar
						<< "Bar: ";
					i = 0;
					while (i < p1Health)
					{
						cout << "X";
						i++;
					}
					cout << endl << endl;

					if (p2Poison)
					{
						cout << pTwo << " takes poison damage.";
						p2Health -= 5;
						pCounter2++;
						if (pCounter2 == 5)
						{
							pCounter2 = 0;
							p2Poison = false;
						}
						if (p2Health <= 0)
							break;
					}

					cout << pTwo << " select your move." << endl << endl;		//player choose between 4 options to attack/defend/spAttk opponent and item menu
					cout << "A - Attack" << endl;		//outputs menu options
					cout << "B - Magic" << endl;
					cout << "C - Special" << endl;
					cout << "I - Item Menu" << endl << "Selection: ";
					time(&start);
					cin >> selection;
					time(&end);
					cin.ignore(1000, '\n');
					cout << endl;

					s1 = 2;
					selectCheck(selection, s1);		//calls select check function

					if (selection == 'a')		//attack function
					{
						timer = difftime(end, start);
						srand(timer);
						x = rand() % 100 + 1;


						if (x <= p2Stats[0])		//checks hit percentage
						{
							if (x <= 1)		//checks if player misses
							{
								cout << "O.o Critical Miss o.O" << endl
									<< pTwo << "takes 5 damage." << endl;
								p2Health -= 5;
							}
							else if (x <= p1Stats[4] && x > 1)		//checks for critical damage
							{
								cout << "*** Critical hit! ***" << endl;
								damage = p2Stats[1] + (p2Stats[1] / 2);
							}
							else
								damage = p2Stats[1];

							damage = static_cast<int> (damage - (damage * p1Stats[5] / 100));
							cout << pTwo << " hits for " << damage << " points." << endl;
							p1Health -= damage;
						}
						else
							cout << pTwo << " swings and misses." << endl;
					}
					else if (selection == 'b')
					{
						//magic
						damage = p2Stats[2];
						damage = damage - (damage * p1Stats[6] / 100);
						cout << pTwo << " uses magic for " << damage << " points of damage." << endl;
						p2Magic -= 10;
						p1Health -= damage;
					}
					else if (selection == 'c')
					{
						//special
						if (p2Special >= 25)
						{
							cout << "Stamina - 25 pts." << endl;
							p2Special -= 25;

							if (p2Class == "Barbarian")		//special barbarian method
							{
								srand(selection);
								x = rand() % 100 + 1;

								if (x <= 50)
								{
									cout << pTwo << " uses Bash." << endl;
									damage = static_cast<int> (p2Stats[3] - (p2Stats[3] * p1Stats[6] / 100));
									p1Health = p1Health - damage;
								}
							}
							else if (p1Class == "Mage")		//special mage method
							{

								cout << pTwo << " uses Healing Magic." << endl;
								p2Health += 25;
							}
							else		//special rogue method
							{
								q = 0;
								cout << pTwo << " uses Quick Hits with ";
								for (i = 0; i<3; i++)
								{
									srand(selection);
									x = rand() % 100 + 1;

									if (x >= 50)
									{
										q++;
										damage = static_cast<int> (p2Stats[1] - (p2Stats[1] * p1Stats[6] / 100));
										p1Health -= damage;
										cout << q << " hits for " << damage << " damage" << endl;
									}
								}
							}
						}
						else
							cout << pTwo << " tries to use special but doesn't have enough Stamina." << endl;
					}
					else if (selection == 'i')		//item menu method
					{
						cout << "Items:" << endl		//outputs item menu
							<< "A - Health Potion: " << hPotion2 << endl
							<< "B - Mana Potion: " << mPotion2 << endl
							<< "C - Poison: " << pPotion2 << endl
							<< "Selection: ";
						cin >> selection;
						cin.ignore(1000, '\n');
						cout << endl;
						s1 = 1;
						selectCheck(selection, s1);		//calls select check function

						if (selection == 'a')		//health potion method
						{
							if (hPotion2 > 0)
							{
								cout << pTwo << " uses health potion. +25HP" << endl;
								p2Health += 25;
								hPotion2--;
							}
							else
								cout << "Not enough health potions." << endl;
						}
						else if (selection == 'b')		//mana potion method
						{
							if (mPotion2 > 0)
							{
								p2Magic += 25;
								mPotion2--;
							}
							else
								cout << "Not enough mana potions." << endl;
						}
						else		//poison potion method
						{
							if (pPotion2 > 0)
							{
								cout << pTwo << " uses poison." << endl;
								p1Poison = true;
								pPotion2--;
							}
							else
								cout << "Not enough poison potions." << endl;
						}


					}

					system("Pause");
					p2Turn = false;
					p1Turn = true;
				}

				if (p1Health <= 0 || p2Health <= 0)		//check player health and end turns if <=0
				{
					turns = false;
					break;
				}
			}

			play = false;		//sets play loop and any poison effects to false and resets poison counters
			p1Poison = false;
			pCounter1 = 0;
			p2Poison = false;
			pCounter2 = 0;

			if (p1Health > 0)		//player one win method
			{
				p1Winner = 1;
				p1Score++;
				p1Stats[7]++;

				cout << pOne << " is the Winner! Ready for your perks!?" << endl << endl;

				cout << "Select a stat boost:" << endl;		//offers a stat boost menu for player 1 if won
				for (int q = 0; q<5; q++)
					if (p1StatBoosts[q])
						cout << statBoosts[q] << endl;
				cin >> selection;
				cin.ignore(1000, '\n');
				s1 = 3;
				selectCheck(selection, s1);		//calls selection check function

				switch (selection)		//implements stat boost based on selection
				{
				case 'a':
					p1Boost[0] += 1;
					break;
				case 'b':
					p1Boost[1] += 1;
					break;
				case 'c':
					p1Boost[2] += 5;
					break;
				case 'd':
					p1Boost[3] += 5;
					break;
				case 'e':
					p1Boost[4] += 5;
					break;
				}
			}
			else		//player two win method
			{
				p2Winner = 1;
				p2Score++;
				p2Stats[7]++;

				cout << pTwo << " is the Winner! Ready for your perks!?" << endl << endl;

				cout << "Select a stat boost:" << endl;
				for (int q = 0; q<5; q++)
					if (p1StatBoosts[q])
						cout << statBoosts[q] << endl;
				cin >> selection;
				cin.ignore(1000, '\n');
				s1 = 3;
				selectCheck(selection, s1);

				switch (selection)
				{
				case 'a':
					p2Boost[0] += 1;
					break;
				case 'b':
					p2Boost[1] += 1;
					break;
				case 'c':
					p2Boost[2] += 5;
					break;
				case 'd':
					p2Boost[3] += 5;
					break;
				case 'e':
					p2Boost[4] += 5;
					break;
				}
			}

			p1Stats[8]++;		//increments games played stat for p1 and p2
			p2Stats[8]++;

			cout << pOne << " score: " << p1Score << endl;		//outputs each player's scores
			cout << pTwo << " score: " << p2Score << endl;

			if (p1Score > p2Score)		//outputs congratulations message based on winning player
				cout << "Congrats " << pOne << ", you defeated " << pTwo << " by " << (p1Score - p2Score) << " point(s)." << endl << endl;
			else if (p2Score > p1Score)
				cout << "Congrats " << pTwo << ", you defeated " << pOne << " by " << (p2Score - p1Score) << " point(s)." << endl << endl;
			else
				cout << "Great Job " << pOne << " and " << pTwo << ", you tied!" << endl << endl;


			cout << pOne << " would you like to save your character? (y) or (n)" << endl;		//offers to save player one stats
			cin >> saveChar;
			cin.ignore(1000, '\n');
			if (tolower(saveChar) == 'y')		//player 1 save method	Cut/ || saveChar == 'Y' / and added tolower()
			{
				outFileA.open(pOne + ".txt");
				outFileA << pOne << " ";
				for (i = 0; i<5; i++)
					outFileA << p1Boost[i] << " ";
				outFileA << "\n";
				for (i = 0; i<9; i++)
					outFileA << p1Stats[i] << " ";
				outFileA.close();
			}

			cout << pTwo << " would you like to save your character? (y) or (n)" << endl;		//offers to save player two stats
			cin >> saveChar;
			cin.ignore(1000, '\n');
			if (saveChar == 'y' || saveChar == 'Y')		//player 2 save method
			{
				outFileB.open(pTwo + ".txt");
				outFileB << pTwo << " ";
				for (i = 0; i<5; i++)
					outFileB << p2Boost[i] << " ";
				outFileB << "\n";
				for (i = 0; i<9; i++)
					outFileB << p2Stats[i] << " ";
				outFileB.close();
			}


			cout << "Would you like to play again? (y) or (n)" << endl;		//request another game
			cin >> playGame;		//user inputs character value for play again
			cin.ignore(1000, '\n');

			if (playGame != 'y' && playGame != 'Y')		//play again check
				game = false;		//play again game state is set to false
			else		//play again method
			{
				play = true;
				turns = true;
				cout << "Would you like to change player health settings? (y) or (n): " << endl;		//requests new health settings
				cin >> selection;
				cin.ignore(1000, '\n');
				if (selection == 'y' || selection == 'Y')
					pickHealth = true;		//sets pick health method to true so players may change settings for next loop
				playerStatus(p1Health, p2Health, p1Magic, p2Magic, p1Special, p2Special, hPotion1, mPotion1, pPotion1, hPotion2, mPotion2, pPotion2, pH);		//calls player stat reset function
			}
			system("pause");		//holds screen for user
			system("cls");		//clears screen for new game
		}
	}
}

/* TODO: known required fixes
save files not acquiring correct stats
add random number modifier for +/-(5) damage each attack
*/