#ifndef _LINKEDLIST_
#define _LINKEDLIST_

#include <string>
#include "LLN.h"
using namespace std;

class LLN;
class LinkedList {
public:	

	LLN *head;
	int count;
	LinkedList ();
	~LinkedList ();
	int ct;
	void push(int N);
	int pop();
	void print();
	void printfirst(int t);
};
#endif
