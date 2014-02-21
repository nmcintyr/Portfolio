/*Name: Nick McIntyre-Wyma

  Program: This program is made to simulate a deck of cards, and being able to manipulate a linked list by adding, deleting, and swapping
  nodes to do the actions required by the user.							*/
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "LLN.h"
#include "MainLL.h"
#include <cstdlib>
#include <time.h>
#include <ctime>
using namespace std;

int main (int argc, char **argv)
{
	srand((int)time(NULL));				//Initializing this for later use in the shuffling method. Uses the time to get a true random number, instead of
	int count = 0;						//the normal "psuedo-random" number.
	int r =0;
	int t =0;
	int dealn = 0;
	LinkedList *MyLL = new LinkedList();
	string u = "";
	while (true)
	{
	cout << "What do you want to do?  ";
	cin >> u;
	cout << u << endl;
	if (u == "INITIALIZE" || u=="Initialize" || u == "initialize")//If the user selects "Initializing" then the program deletes  
	{															  //the old linkedlist and makes a new one, adding the nodes and then shuffling.
		MyLL->deleteall();
		for (int i = 0; i < 13; i++)
		{ 
			string rank = "";
			if (i+1 == 1){rank = "ACE";}
			else if (i+1 == 2){rank = "TWO";} 
			else if (i+1 == 3){rank = "THREE";}
			else if (i+1 == 4){rank = "FOUR";}
			else if (i+1 == 5){rank = "FIVE";}
			else if (i+1 == 6){rank = "SIX";}
			else if (i+1 == 7){rank = "SEVEN";}
			else if (i+1 == 8){rank = "EIGHT";}
			else if (i+1 == 9){rank = "NINE";}
			else if (i+1 == 10){rank = "TEN";}
			else if (i+1 == 11){rank = "JACK";}
			else if (i+1 == 12){rank = "KING";}
			else if (i+1 == 13){rank = "QUEEN";}
			for (int y=1;y<=4;y++)
			{
				if (y==1) {MyLL->add(rank,"HEARTS");}
				else if (y==2) {MyLL->add(rank,"DIAMONDS");}
				else if (y==3) {MyLL->add(rank,"CLUBS");}
				else if (y==4) {MyLL->add(rank,"SPADES");}
				else;
			}
		}
		count = MyLL->count();
		if (count > 0)
		{
		for (int q= 0; q < 1000;q++)
		{
			r=(rand()%count);
			if (r<3){r+=3;}
			MyLL->shuffle(r);
		}
		}
		else;
	}
	else if (u=="Print" || u == "PRINT" || u == "print") // Prints the deck.
	{
	MyLL->print();
	}
	else if (u == "shuffle" || u == "SHUFFLE" || u == "Shuffle") // Swaps the first node of the "deck" with one random node in the deck
	{															 // and then repeats to shuffle.
		count = MyLL->count();
		cout << "Shuffling cards.... " << endl;
		if (count > 0)
		{
		for (int q= 0; q < 1352;q++)			//Goes through and shuffles the first card in the deck with one random card in the deck. Does this 1352 times 
		{										//for good measure.
			r = (rand()%count);//Gets a random number based on system time
			if (r<3){r+=3;}
			MyLL->shuffle(r);
		}
		cout << "Shuffled." << endl;
		}
		else 
			cout << "There is nothing to shuffle!" << endl;
	}
	else if (u == "DEAL" || u == "Deal" || u == "deal")			//Deletes the first x cards in the deck then prints out how many cards are left.
	{
		cin.ignore();
		cin >> dealn;
		MyLL->deal(dealn);

	}
	else if (u == "DELETE" || u == "delete" || u == "Delete") // Deletes every card of a certain suite or number in the deck.
	{
		cin.ignore();
		cin >> u;
		cout << u << endl;
		MyLL->deletes(u);
	}
	else if (u == "EXIT" || u == "Exit" || u == "exit") // Breaks the loop and ends the program.
	{
		break;
	}
	}
	system("pause");
	return 0;
}