#ifndef _SORTS_
#define _SORTS_
#include <string>
using namespace std;

fstream words;

int main (int argc, char **argv);
void ShellSort (string fname,int num, int sz);
string getword (int wn, int num);
void setword (int num, int wn, string w);
#endif