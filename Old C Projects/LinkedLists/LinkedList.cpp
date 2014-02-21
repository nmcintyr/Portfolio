


#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

LinkedList::LinkedList () 
{
	head = NULL;
	ct = 0;
}

void LinkedList::add (string rank, string suite) //Adds a node to the Linked List.
{
	if (head==NULL){head = new LLN (rank,suite,NULL);}
	else {head->add (rank,suite);}
	ct++;
}

void LinkedList::print()
{
	if (head == NULL)
		cout << "There is nothing to print!" << endl;
	else 
		head->print();
}

int LinkedList::count(){return ct;}

string LinkedList::whathead() //Returns what the head is.
{
	return head->r;
}

void LinkedList::shuffle(int count) //Swaps the first node of the linked list with a random node in the linked list.
{
if (head == NULL){cout << "There is nothing to shuffle!" << endl;return;}
else 
{
	LLN *x = head->shuffle(count,NULL);
	x->next = head;
	head = x;
}
}

void LinkedList::deal(int dealn) // Deletes the first "dealn" number of nodes from the linked list. 
{
	if (head == NULL || dealn > ct)
	{
		cout << "There aren't enough cards left to deal!" << endl;
		return;
	}
	else
	{ 
		ct = ct-dealn;
		head = head->deal(dealn,x);
		cout << dealn << " Cards dealt. " << endl;
		cout << ct << " cards left." << endl;
	}
}

void LinkedList::deletes(string st) //Deletes all of the nodes that match "st" as long as there is a linked list.
{
if (head == NULL)
	cout << "There is nothing there!" << endl;
else
{
	head = head->deletes(st, NULL,ct);
}
}
void LinkedList::deleteall()
{
	if(head==NULL) return;
	head = head->deleteall(ct);
	return;
}