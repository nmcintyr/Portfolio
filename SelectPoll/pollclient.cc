//Name: Nick McIntyre-Wyma
//Project: This project was made to test how to correctly use select and poll, this being the client code.
#include <iostream>		
#include <stdio.h>	
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <string>
using namespace std;
const int BUFSIZE=1024;

void Error(const char *msg)
{
	perror(msg);
	exit(1);
}

int MakeSocket(char *host, char *port) {
	int s; 	// int to hold the socket number, errors if its == -1		
	int len; // int that holds the # of bytes read/written
	struct sockaddr_in sa; //A new structure for socket info
	struct hostent *hp;//A new structure for host info
	struct servent *sp;// A new structure for server name/port/stuff
	int portnum;	//int holding the port number
	int ret;		//holds the file descriptor for sockets

	hp = gethostbyname(host);
	if (hp == 0) 
		Error("Gethostbyname");
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		if (sp == NULL)
			Error("getservbyname");
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	if (s == -1) 
		Error("socket");
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	if (ret == -1)
		Error("connect");
	cout << "Connect to host " << host  << " port " << port << endl;
	return s;
}

main(int argc, char *argv[]) {


	int s; 		
	int len;	
	char buf[BUFSIZE];
	int ret;	
	s = MakeSocket(argv[1], argv[2]);
	int keyboard = 0;
	struct pollfd pollfds[2];
 	pollfds[0].fd = keyboard;		// setting to the keyboard
	pollfds[0].events = POLLIN;
	pollfds[1].fd = s;			//setting to the socket
	pollfds[1].events = POLLIN;


	while ( 2 < 3)
	{	
		int error=poll(pollfds, 2, 10000);
		if (error == -1)
			perror("Poll poopy:");
		else if (pollfds[0].revents & POLLIN)	//if from keyboard
		{
			string junk;
			getline(cin,junk);
			strcpy(buf,(char *)junk.c_str());
			len = junk.length();
			if (junk == "quit")
			{
				close(s);
				break;
			}
			else
			{
				len = write(s,buf,len);					
				if (len < 0)
				perror("Write");
			}
		}
		else if (pollfds[1].fd != 0 && pollfds[1].revents & POLLIN)	//if from socket
		{
			int len = read(pollfds[1].fd, buf, 100);
			if (len > 0) {
				buf[len] = 0;
				cout << buf << endl;
			}
			else
			{
				perror("Unable to read");
				close(s);
				pollfds[1].fd = 0;
				cout << "BLEURRRRGHHHH !!!!!!       AUUGHHHHH !!!!!! " << endl;
				cout <<"CLOSING THE CLIENT!" << endl;;
				break;
			}
		}
		else
		{
		}
	}
	system("pause");
}
