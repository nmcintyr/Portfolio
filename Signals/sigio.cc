//Name: Nick McIntyre-Wyma
//Project: This program is made to test signal handling.

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <signal.h>
#include <fcntl.h>
using namespace std;

volatile double sum=0; // This can be improved
int s;

int MakeServerSocket(const char *port) {
	const int MAXNAMELEN = 255;
	const int BACKLOG = 3;	
	char localhostname[MAXNAMELEN]; // local host name
//	int s; 		
	int len;
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;

	hp = gethostbyname("cs.nmu.edu");

	sscanf(port, "%d", &portnum);
	if (portnum ==  0) {
		sp=getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);

	ret = bind(s, (struct sockaddr *)&sa, sizeof(sa));

	listen(s, BACKLOG);
	cout << "Calculating Pi, and waiting for connection on port " << port << endl;
	return s;
}

// This gets called whenever there is an event on a fd
void sighandler(int signo)
{
	char buf[1024];
	int ret;		// return code from various system calls
	struct sockaddr_in sa;
	int sa_len = sizeof(sa);
	int fd = 0;
	int len = 0;
    if (signo==SIGIO)
	{
		fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len);
		len = 0;
		sprintf(buf,"%g",sum);
		cout << "Sending this: " << buf << endl;
		ret = write(fd,buf,strlen(buf)+1);
		if (ret < 0)
			perror("Write");
	}
	close(fd);
    return;
}



int main(int argc, char **argv)
{
	double x = 0;
	double y = 0;
	double dist = 0;
	double tempsum = 0;
	int i = 0;
    int count;
	s = MakeServerSocket("40903");
 
    // Set up the signal handler to call the function above
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = sighandler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGIO, &action, NULL);


    // Set up the file descriptor to generate a signal
    fcntl(s, F_SETOWN, getpid());
    fcntl(s, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | FASYNC);


    while(1) 
	{
	i++;
	x =(double)rand()/(double)RAND_MAX;		//RAND_MAX gives the maximum number rand() can get. Using it here garuntees x and y will be *at most* 1
	y =(double)rand()/(double)RAND_MAX;
	dist = sqrt((x*x)+(y*y));
	if (dist < 1.00)
		{
			tempsum++;
		}
	sum = (tempsum/i) * 4;//Now that there is a lock, modifies the global variable "sum".
		//	cout << "Pi: " << sum << endl;
    }
}

