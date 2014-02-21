#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

LinkedList::LinkedList ()
{
	head = NULL;
	ct = 0;
}

LinkedList::~LinkedList ()
{
	cout << "Deleting the Linked List!" << endl;
	delete head;
}

int LinkedList::pop()
{
	int val;
	if (head == NULL){return 0;}
	else 
	{
		val = head->getnum();
		head = head->pop();
	}
	return val;
}

void LinkedList::push (int N) 
{
	if (head==NULL){head = new LLN (N,NULL);}
	else 
	{
		LLN *p = new LLN (N,head);
		head = p;
	}
	ct++;
}

void LinkedList::print()
{
	if (head == NULL)
		cout << "There is nothing to print!" << endl;
	else 
	{
		head->print();
	}
}

	