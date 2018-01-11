#include<iostream>
#include<string>

#include "stdafx.h"
#include "functions.h"

using namespace std;

void playerStatus(double& p1H, double& p2H, double& p1M, double& p2M, double& p1S, double& p2S,
	int& p1HP, int& p1MP, int& p1PP, int &p2HP, int& p2MP, int& p2PP, char pH)
{
	switch (pH)
	{
	case 'a':
		p1H = 50;		//resets player health status to half
		p2H = 50;
		break;
	case 'b':
		p1H = 100;		//resets player health status to nominal
		p2H = 100;
		break;
	case'c':
		p1H = 250;		//resets player health status to 250%
		p2H = 250;
		break;
	}

	p1M = 50;		//resets player magic status to default
	p2M = 50;
	p1S = 100;		//resets player special status to default
	p2S = 100;

	p1HP = 2;		//resets player 1 potion count
	p1MP = 2;
	p1PP = 2;

	p2HP = 2;		//resets player 2 potion count
	p2MP = 2;
	p2PP = 2;
}