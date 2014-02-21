//Name: Nick McIntyre-Wyma
//Class: CS222
//Program: This program performs the "Towers of Hanoi" problem using stacks and push, pop, and isempty methods. 
#include <iostream>
#include <cstdlib>
#include "LinkedList.h"
#include "LLN.h"
#include "PG3.h"
#include <math.h>
using namespace std;

int main (int argc, char **argv) 
{
	int discs = atoi(argv[1]);
	string d;
	Hanoi (discs);
	system("pause");
	return 0;
}

void Hanoi (int discs)
{
	double reqmoves = pow(2.0,discs) -1;
	for(int i = discs; i >0; i--){pole1->push(i);}
	while(discs%2 == 0)
	{
		movemethod1();		//moving from pole 1 to pole 2 or vice-versa
		reqmoves--;
		if (reqmoves == 0){break;}

		movemethod2();		//moving from pole 1 to pole 3 or vice versa
		reqmoves--;
		if (reqmoves == 0){break;}

		movemethod3();		//moving from pole 2 to pole 3 or vice versa
		reqmoves--;
		if (reqmoves == 0){break;}
	}

	while(discs%2!=0)
	{
		movemethod2();		//moving from pole 1 to pole 3 or vice versa
		reqmoves--;
		if (reqmoves == 0){break;}

		movemethod1();		//moving from pole 1 to pole 2 or vice-versa
		reqmoves--;
		if (reqmoves == 0){break;}

		movemethod3();		//moving from pole 2 to pole 3 or vice-versa
		reqmoves--;
		if (reqmoves == 0){break;}
	}
	return;
}

void movemethod1()
{
	int moved1 = pole1->pop();
	int moved2 = pole2->pop();
	if (moved1 == 0){pole1->push(moved2); cout << "Moved disk " << moved2 <<" from Pole 2 to Pole 1 .." << endl;}
	else if (moved2 == 0){pole2->push(moved1); cout << "Moved disk "<<moved1<<" from Pole 1 to Pole 2 .." << endl;}
	else
	{
		if(moved1 > moved2){pole1->push(moved1);pole1->push(moved2);cout << "Moved disk "<<moved1<<" from Pole 2 to Pole 1 .." << endl;}
		else {pole2->push(moved2);pole2->push(moved1); cout << "Moved disk "<<moved2<<" from Pole 1 to Pole 2 .." << endl;}
	}
	return;
}

void movemethod2()
{
	int moved1 = pole1->pop();
	int moved2 = pole3->pop();
	if (moved1 == 0){pole1->push(moved2);  cout << "Moved disk "<<moved2<<" from Pole 3 to Pole 1 .." << endl;}
	else if (moved2 == 0){pole3->push(moved1); cout << "Moved disk "<<moved1<<" from Pole 1 to Pole 3 .." << endl;}
	else
	{
		if(moved1 > moved2){pole1->push(moved1);pole1->push(moved2); cout << "Moved disk "<<moved2<<" from Pole 3 to Pole 1 .." << endl;}
		else {pole3->push(moved2);pole3->push(moved1); cout << "Moved disk "<<moved1<<" from Pole 1 to Pole 3 .." << endl;}
	}
return;
}

void movemethod3()
{
	int moved1 = pole2->pop();
	int	moved2 = pole3->pop();
	if (moved1 == 0){pole2->push(moved2); cout << "Moved disk "<<moved2<<" from Pole 3 to Pole 2 .." << endl;}
	else if (moved2 == 0){pole3->push(moved1);  cout << "Moved disk "<<moved1<<" from Pole 2 to Pole 3 .." << endl;}
	else
	{
		if(moved1 > moved2){pole2->push(moved1);pole2->push(moved2); cout << "Moved disk "<<moved2<<" from Pole 3 to Pole 2 .." << endl;}
		else {pole3->push(moved2);pole3->push(moved1); cout << "Moved disk "<<moved1<< " from Pole 2 to Pole 3 .." << endl;}
	}
	return;
}