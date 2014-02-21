//Name: Nick McIntyre-Wyma
//Project: This project was made to test how to correctly use select and poll, this being the server code. 

#include <sys/time.h>
#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

int acceptarray[20];
string namearray[20];
int pos =0;

int MakeServerSocket(const char *port) {
	const int MAXNAMELEN = 255;
	const int BACKLOG = 3;	
	char localhostname[MAXNAMELEN]; 
	int s; 		
	int len;
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;

	gethostname(localhostname,MAXNAMELEN);
	hp = gethostbyname("euclid.nmu.edu");
	
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
	cout << "Waiting for connection on port " << port << " hostname " << localhostname << endl;
	return s;
}
void saystuff(int p)
{
	//cout << "It gets to saystuff" << endl;
	char buf[1024];
	char buf2[1024];
	for (int i=0;i<1024;i++){buf[i]=0; buf2[i]=0;}
	int len = 0;
	string name="";		//setname(p);	//Gets the name of the person
	//strcpy(buf,(char *)name.c_str());
	//cout << buf2 << endl;
	len = read(acceptarray[p], buf2, 100);
	if (len <= 0)
		perror("Read:");
	if (buf2[0] == 'n' && buf2[1] == 'a' && buf2[2] == 'm' && buf2[3] == 'e')
	{
		for (int n =4;n<len;n++)
		{
			cout << buf << endl;
			name = name+buf2[n];
			cout << name << endl;
		}
		namearray[p] = name+":";
		name = "";
		cout << "Client setting name to "<<namearray[p]<<" ..." <<endl;
	}
	if (buf2[0] == '/' && buf2[1]=='o')
	{
	strcpy(buf,(char *)namearray[p].c_str());
	strcat(buf,buf2);
	len = namearray[p].length() + len;
	cout << buf << endl;
	if (len > 0 ) 
	{
			len = write(acceptarray[0],buf,len);					
			if (len < 0)
			perror("Write");
	}
	else
	{
		//perror("Unable to read");
		close(acceptarray[0]);
		acceptarray[0] = acceptarray[pos];
		pos--;
		return;
	}
	}
	else
	{
	buf2[len]=0;
	strcpy(buf,(char *)namearray[p].c_str());
	strcat(buf,buf2);
	len = namearray[p].length() + len;
	cout << buf << endl;
	if (len > 0 ) 
	{
		//len+=7;	
		//buf[len] = 0;
		//cout << namearray[p]<<" says " << buf <<"." << endl;
		for(int pos2=0;pos2<pos;pos2++)
		{
			if (pos2 != p)
				{
					len = write(acceptarray[pos2],buf,len);					
					if (len < 0)
					perror("Write");
				}
		}
	}
	else
	{
		//perror("Unable to read");
		close(acceptarray[p]);
		acceptarray[p] = acceptarray[pos];
		pos--;
		return;
	}
	}
}

int findmax(int pos)
{
	int max =0;
	for(int i =0;i<pos;i++)
	{
		if (max < acceptarray[i])
			max = acceptarray[i];
	}
	return max;
}



int main(int argc, char *argv[]) {

	int socket = MakeServerSocket("40901");
	int client = -1;
	int keyboard = 0;
	while ( 2 < 3)
	{
		struct timeval timeout;
	
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;	
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(keyboard, &rfds);
		FD_SET(socket, &rfds);
		for(int p=0;p<pos;p++){FD_SET(acceptarray[p],&rfds);}	//resets the rfds
		int error = select(max(max(findmax(pos), keyboard), socket)+1, &rfds, 0, 0, &timeout);
		if (error == -1)
			perror("Select poopy:");
		else if (FD_ISSET(keyboard, &rfds))
		{
			string junk;
			cin >> junk;
			if(junk == "list")				//Lists the people currently connected
			{
				for(int list=0;list<pos;list++)
				{
					cout << namearray[list] << " is connected at " << acceptarray[list] << endl;
				}
			}
			else if (junk == "quit")
			{
				for(int c =0;c<pos;c++)
				{
					close(acceptarray[c]);
				}
				break;
			}

			else
				cout << junk << endl;
		}
		else if (FD_ISSET(socket, &rfds))	//if someone is trying to connect, it will add them to the acceptarray
		{
			cout << "Some one tried me\n";
			struct sockaddr_in sa;
			int sa_len = sizeof(sa);
			client = accept(socket, (struct sockaddr *)&sa, (unsigned int *)&sa_len);
			if (client == -1)
				perror("Accept bad");
			acceptarray[pos] = client;

			FD_SET(acceptarray[pos],&rfds);
			pos++;
		}
	
		else if (pos>0)
		{
				for(int p = 0;p<pos;p++)
				{
					if (FD_ISSET(acceptarray[p], &rfds))
					{
					saystuff(p);
					}
				}
		}

		else
		{
			//cout << "timeout\n";
		}
	}
}