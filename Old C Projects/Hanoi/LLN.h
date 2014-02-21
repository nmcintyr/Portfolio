#ifndef _LLN_
#define _LLN_
#include <string>
#include "LinkedList.h"
using namespace std;

class LinkedList;

class LLN {
private:
int Num;
LLN *next;
public:
LLN * getnext();
void setnext(LLN *p);
int getnum();
LLN (int N, LLN *n);
~LLN ();
void print ();
LLN * push (int N);
LLN * pop();
};
#endif