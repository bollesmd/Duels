#pragma once
#include<iostream>
#include<string>

using namespace std;		//uses namespace std


char selectCheck(char select, int s1);		//initializes selection check function

//initializes player status "reset" function
void playerStatus(double& p1H, double& p2H, double& p1M, double& p2M, double& p1S, double& p2S, 
					int& p1HP, int& p1MP, int& p1PP, int &p2HP, int& p2MP, int& p2PP, char pH);

//Player Functions
