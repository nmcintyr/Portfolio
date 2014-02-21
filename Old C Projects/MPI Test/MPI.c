/*Name: Nick McIntyre-Wyma
  Project: Testing MPI using C to calculate collatz numbers by splitting up the work.*/
include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long int table[1000000]={};
int collatz(unsigned long int value);
int printc(unsigned long int value);
#define MASTER		0

int main (int argc, char* argv[])
{
	int winners[9];
	int taskid, numtasks, rc, i, count, max, maxc, totalmax, len;
    max=0;
	MPI_Status status;
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &taskid);        
	MPI_Comm_size (MPI_COMM_WORLD, &numtasks);  
	int tempMaxc[numtasks];
	count = 1000000/numtasks;						//Splitting up the work just by number of nodes
	int start = taskid*count;
	printf ("MPI task %d has started and is covering %d through %d\n", taskid, start, start+count);
	for (int q=start+1; q < start+count; q++){	
		len = collatz(q);
		table[q] = len;
		if (len > max){
			max = len;	//Max holds the current winner in length
			maxc = q;	//Maxc holds what number produced the longest collatz
		}
	}
	printf("Longest string of collatzs for process %d is: %d\n", taskid, max);
	rc = MPI_Reduce(&max, &totalmax, 1, MPI_INT, MPI_MAX, MASTER, MPI_COMM_WORLD);	//Reduce and get totalmax
	MPI_Gather(&maxc, 1, MPI_INT, &tempMaxc, 1, MPI_INT, MASTER, MPI_COMM_WORLD);	//Gathers all the winner numbers in an array.
	if (rc != MPI_SUCCESS)
		printf("%d: failure on mpc_reduce\n", taskid);
	if (taskid == MASTER)
	{
		printf("Longest string of collatzs is: %d\n", totalmax);
		for (int q = 0; q < numtasks; q++){
			if (collatz(tempMaxc[q]) == totalmax){ 
				printf("This is the sequence for the largest collatz: \n");	//Printing the collatz sequence
				printc(tempMaxc[q]);
			}
		}
	}
	MPI_Finalize();
	return 0;								
}

int printc(unsigned long int value){
	printf("%lu   ", value);
	if (value == 1)
		return 1;
	else if (value % 2 == 0)
		return 1 + printc(value/2);
	else
		return 1 + printc(3*value+1);
}

int collatz (unsigned long int value){
	//printf("%d\n", value);
	if (value <= 1000000){
		if (value == 1)
			return 1;
		else if (value % 2 == 0){
			if (table[value] == 0){
				table[value] = 1+collatz(value/2);
				//return 1 + collatz(value/2);
			}
			return table[value];
			}
		else{
			if (table[value] == 0){
				table[value] = 1 + collatz(3*value+1);
				//return 1 + collatz(value/2);
			}
			return table[value];
			}
	}
	if (value % 2 == 0)
		return 1 + collatz(value/2);
	else
		return 1 + collatz(3*value+1);
}