#include <string>
#include <iostream>
#include "LLN.h"

LLN::LLN (int N, LLN *n) 
{
 Num = N;
 next = n;
}

LLN * LLN::getnext(){return next;}
int LLN::getnum(){return Num;}
void LLN::setnext(LLN *p){next=p;}

LLN::~LLN () 
{
	cout << "Deleting node " << Num << endl;
	delete next;
}

void LLN::print ()
{ 
	cout << Num << endl;
	if(getnext()!=NULL)	next->print();
	return;
}

LLN * LLN::pop()
{
	LLN *p = getnext();
	return p;
	delete this;
}