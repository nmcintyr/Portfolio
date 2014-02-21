//Name: Nick McIntyre-Wyma
//Program: Small test code to help understand mutex locks
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

pthread_mutex_t aMutex= PTHREAD_MUTEX_INITIALIZER;
void* MyThreadFunc(void* arg);

int theSum = 0;

int main(void){

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, MyThreadFunc, (void *)NULL);
	pthread_create(&thread2, NULL, MyThreadFunc, (void *)NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	cout << theSum << endl;
}

void* MyThreadFunc(void* arg){
	for(int i=0;i<10*1000*1000;i++){
		pthread_mutex_lock(&aMutex);
		theSum++;
		pthread_mutex_unlock(&aMutex);
	}
	return((void*)NULL);
}

