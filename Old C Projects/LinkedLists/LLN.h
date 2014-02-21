#ifndef _LLN_
#define _LLN_
#include <string>
#include "LinkedList.h"
using namespace std;

class LinkedList;

class LLN {
public:
string r;
string s;
LLN *next;
LLN *x;
LLN (string rank, string suite, LLN *n);
//void deletefull ();
void print ();
LLN * add (string rank,string suite);
LLN * shuffle(int count, LLN *p);
LLN * deal (int dealn, LLN *x);
LLN * deletes(string st, LLN *p,int &ct);
LLN * deleteall(int &ct);
};
#endif