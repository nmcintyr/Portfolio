//Name: Nick McIntyre-Wyma
//Program: This program is made to use threads to find the rough estimate value
// of PI using the Monte Carlo method.
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;


#define NUM_THREADS 10
pthread_t tid[NUM_THREADS]; //Making the array of thread ID's
pthread_mutex_t aMutex= PTHREAD_MUTEX_INITIALIZER; // Mutex lock thingy
void* MyThreadFunc(void* arg);//Thread creation process
double sum = 0;

int main(void)
{
	for(int i=0;i<NUM_THREADS;i++)	//Creates all the threads using the tid array
            pthread_create(&tid[i], NULL, MyThreadFunc,(void*)NULL);

	for(int j=0;j<NUM_THREADS;j++)	//Joins all the threads so we wait for them all to complete.
		pthread_join(tid[j], NULL);
	cout<<"Main finished\n";
	cout << (sum/1000000)*4 << endl;
}

void* MyThreadFunc(void* arg)
{	

	double x = 0;
	double y = 0;
	double dist = 0;
	double tempsum = 0;
	for(int i=0;i<100000;i++)
	{
		x =(double)rand()/(double)RAND_MAX;		//RAND_MAX gives the maximum number rand() can get. Using it here garuntees x and y will be *at most* 1
		y =(double)rand()/(double)RAND_MAX;
		dist = sqrt((x*x)+(y*y));
		if (dist < 1.00)
			tempsum++;
	}
	pthread_mutex_lock(&aMutex);//Starts the lock only after all the work has been done, to make sure it has it locked for as little time as possible.
	sum = sum + tempsum;//Now that there is a lock, modifies the global variable "sum".
	pthread_mutex_unlock(&aMutex);//Ends the lock
	return((void*)NULL);
}

