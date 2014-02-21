#ifndef _LINKEDLIST_
#define _LINKEDLIST_

#include <string>
#include "LLN.h"
using namespace std;

class LLN;

class LinkedList {
public:	
	LLN *head;
	LLN *x;
	LinkedList ();
	string whathead();
	void deleteall();
	int ct;
	void add (string rank, string suite);
	void print();
	int count();
	void shuffle (int count);
	void deal(int dealn);
	void deletes(string st);
};
#endif