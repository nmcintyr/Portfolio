#include <string>
#include <iostream>
#include "LLN.h"

LLN::LLN (string rank, string suite, LLN *n) 
{
 r = rank;
 s = suite;
 next = n;
}

void LLN::print () // Prints out every node in the linked list.
{ 
	cout << r << " OF " << s << endl;
	if (next != NULL) next->print ();
}

LLN * LLN::add(string rank,string suite) // Adds a node to the end of the linked list.
{
	if (next==NULL)
	{
		next = new LLN (rank,suite,NULL);
		return this;
	}
	else 
	{
		next = next->add (rank,suite);
		return this;
	}
}

LLN * LLN::shuffle(int count, LLN *p)  //Counts to a random number 
{
	if (count == 0)
	{
		p->next = next;
		return this;
	}
	else
	{
		count --;
		return next->shuffle(count,this);
	}
}

LLN * LLN::deal(int dealn, LLN *x)
{
	dealn--;
	cout << r << " OF " << s << endl;
	if (dealn == 0)
	{
		if (next == NULL){delete this;return NULL;}
		else
		{
		x = next;
		delete this;
		return x;
		}	
	}
	else 
	{
		return next->deal(dealn,x);
	}

}

LLN * LLN::deletes(string st, LLN *p,int &ct)
{
if (next != NULL) 
{
	next = next->deletes(st,this,ct);
}
/*string temp = "";
temp = Num+'0';*/
if (st == r || st == s)
{
	ct--;
	LLN *temp2= next;
	delete this;
	return temp2;
}
else {return this;}
}

LLN * LLN::deleteall(int &ct)
{
	if(next!=NULL)
	{
		next = next->deleteall(ct);
	}
	ct--;
	delete this;
	return NULL;
}