//Name: Nick McIntyre-Wyma
//Program: This program takes a file specified by the user and sorts it using shell sort. 
#include <fstream>
#include <iostream>
#include <string>
#include "Sorts.h"		
using namespace std;

int main (int argc, char **argv)
{
char ch;
string s = "";
int num=0;
int cct = 0;
cout << "Please enter a filename:  ";
string fname = "";
getline (cin,fname);
words.open (fname,ios::in|ios::out|ios::binary);
words.seekg (0,ios::end);
cct = (int)words.tellg();
words.seekg(0);
for (int q = 0;q<4;q++){words.get(ch);s+=ch;}
for (int i=0;i<4;i++)
{
	num=num*10;
	num = num+(s[i]-48);
}
cct=(cct-4)/num;

cout << "There are " << cct << " words in the file!" << endl;
ShellSort(fname,num,cct);
words.close();



system("pause");
return 0;
}

void ShellSort (string fname, int num, int sz) //Method that does the actual sorting.
{	
	int d = sz;
	while (d > 1) {
		if (d%2==1) d = (d+1)/2;
		else if (d==2) d=1;
		else if (d%4==0) d = d/2+1;
		else d = d/2+2;

		for (int i=d; i < sz; i++)
			for (int j=i-d; j>=0; j-=d) 
			{
				string a = getword (j,num);
				string b = getword ((j+d),num);
				if (a > b) {
				setword (num,j,b);
				setword (num,(j+d),a);
				} else break;
			}
	}
}

string getword (int wn, int num) //This method gets the word of given length.
{
	words.seekg ((wn*num)+4);
	string w= "";
	char ch;
	for (int i=0; i < num; i++) {
		words.get (ch);
		w += ch;
	}
	return w;
}

void setword (int num, int wn, string w) //This method writes the given word of given length.
{

	words.seekp ((wn*num)+4);
	for (int i=0; i < num; i++) words << w[i];
}