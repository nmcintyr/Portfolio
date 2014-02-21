// Name: Nick McIntyre-Wyma
// Project: This is a program made to create "stacked deck of cards" so a specific card trick will work. Organizes numbers 1 through n in a specific order.

#include <iostream>
#include <string>
#include "cards.h"		
using namespace std;

int main (int argc, char **argv)
{
int count = -1;
while (count < 0)
{
cout << "Enter a positive int: " << endl;
cin >> count;
cout << "You entered: " << count << endl;
if (count < 1){cout<<"That wasn't a positive int!" << endl;}
}
int final = 0;
int pos=0;
int *A = new int[count];
int *B = new int[count];
for (int q=0; q < count;q++){B[q] = 0;A[q]=0;}

for (int i =1; i <= count;i++)
{
	final = i;
	int j = pos;
	while (final > 0)
	{
		if (B[j] != 1)
		{
			final--;
			if (final == 0)
			{
			A[j] = i;
			B[j] = 1;
			if (j == (count-1)){j=0;}
			else j++;
			break;
			}
			if (j == (count-1)){j=0;}
			else j++;
			}
		else{
		if (j == (count-1)){j=0;}
		else j++;}
		}
	pos = j;
	}



for (int i=0;i<count;i++){cout << A[i]<<" ";}
system("pause");
return 0;
}