//Program: Creates a shell that can run commands and has other functions.
//Created By: Nick McIntyre-Wyma with assistance from Dylan Elliot
//Date: 12/10/2012

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include<readline/readline.h>
#include<readline/history.h>

using namespace std;

void sighandler(int sig) //used for handleing caught keyboard interupts
{
    if(sig == 2){cout<<"Caught Control-C"<<endl;}
    else if(sig == 15){cout<<"Goodbye cruel world"<<endl;exit(0);}
}

void docommand (char **arg_list, char *environment)
{
	char command[350];
	char *path;
	execv(arg_list[0], arg_list);
	path = strtok (environment, ":");
	while( path != NULL)
	{
		strcpy(command, path);
		strcat(command, "/");
		strcat(command, arg_list[0]);
		execv(command, arg_list);
		path = strtok(NULL, ":");
	}
	cout << "Command not recognized!" << endl;
}

void findanddo(char** arg_list, char* environment, int commandcount)
{
	int in, out;

	environment = getenv("PATH"); //grabs the environment
	for(int t=1; t<commandcount; t++)
	{
		if ( strncmp(">", arg_list[t], 1) == 0)	//File redirection, takes the LHS and puts the output to whatever file is listed after ">"
			{
				out = open(arg_list[t+1], O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				if(out == -1)
				{
					cout << "Error writing to file" << endl;
					exit(EXIT_FAILURE);
				}
				dup2(out, 1);
				close(out);
				arg_list[t] = NULL;
				docommand(arg_list,environment);
			}
		else if ( strncmp("<", arg_list[t], 1) == 0)//File redirection, takes the RHS and puts the input to whatever command is listed before "<"
			{
				in = open(arg_list[t+1], O_RDONLY);
				if(in == -1)
				{
					cout << "Error reading file" << endl;
					exit(EXIT_FAILURE);
				}
				dup2(in, 0);
				close(in);
				arg_list[t] = NULL;
				docommand(arg_list,environment);
			}
	}
	docommand(arg_list,environment);
	exit(EXIT_FAILURE); //shouldn't ever get here.
}



void domanycommands(char **arg_list, char *environment, int splitpos, int commandcount)
{
	int childstatus2,childstatus;
	int pfd[2];
	arg_list[splitpos]=NULL;
	char* arg_list2[8];		//second array for the RHS of the pipe
	int start=0;
	for(int i = splitpos+1; i<commandcount;i++)
	{
		arg_list2[start]=arg_list[i];	//setting 
		start++;
	}
	arg_list2[start]=NULL;
	pipe(pfd);						//Piping and giving pfd the file handles.
	if (fork() == 0) // First the child runs
		{
			// This is the child that runs the first half of the pipe.
			dup2(pfd[0], 0); //set stdout to go to the output part of the pipe.
			close(pfd[1]); //Close the inbound, since we are grabbing the output this time.
			findanddo(arg_list2, environment, start); 
		}
	if ((childstatus = fork()) == 0)
		{	//This is the child that runs the other half of the pipe
			dup2(pfd[1], 1);
			close(pfd[0]); //Close the other side of the pipe.
			findanddo(arg_list, environment, splitpos);
		}
	else 
		waitpid (childstatus, NULL, 0);
		close(pfd[1]);
}



int main(int argc, char **argv)
{
	int works;
	works = read_history ("history.txt");
	if(works != 0){cout<<"Error in reading history file."<<endl;}
	signal(SIGABRT, &sighandler);//used for catching signals
	signal(SIGTERM, &sighandler);//sent by keyboard interupts
	signal(SIGINT, &sighandler);//
	char* line;
	char *input1;
	char* arg_list[8];
	char *path, *environment = getenv("PATH");
	char input[350],cmd0[50],cmd1[50],cmd2[50],cmd3[50],cmd4[50],cmd5[50],cmd6[50],command[350]; //this seems rather brute force-ish, might want to fix
	pid_t child;
	int cpid, status, commandcount, out, in, childstatus2, status2, goahead=0;
	setenv("PS1", "<Test Shell Please Ignore>: ", 1);
	while(1)
	{
		printf ("s");
		 cmd0[0] = 0; cmd1[0] = 0;cmd2[0] = 0;cmd3[0] = 0;cmd4[0] = 0;cmd5[0] = 0;cmd6[0] = 0; goahead = 0; //!!!!!!!! still seems bad
		line = readline(getenv("PS1"));//prints out the prompt and returns the input as a char*
		if(line[0]){
		char *expansion;
		int result;
		result = history_expand (line, &expansion);
		if (result)
			fprintf (stderr, "%s\n", expansion);

		if (result < 0 || result == 2)
			{
			free (expansion);
			continue;
			}
		//add_history (expansion);
		strncpy (line, expansion, sizeof (line) - 1);
		free (expansion);}
		strcpy(input,line);
		add_history(line); //add input to arrow history
		free(line); //free the char* for future use

		commandcount = sscanf(input, "%s %s %s %s %s %s %s", cmd0,cmd1,cmd2,cmd3,cmd4,cmd5,cmd6);
		arg_list[0] = cmd0;arg_list[1] = cmd1;arg_list[2] = cmd2;arg_list[3] = cmd3;arg_list[4] = cmd4;arg_list[5] = cmd5;arg_list[6] = cmd6; //seems like terrible code but it works...
		for (int i = 1; i<commandcount; i++)
		{
			if (strncmp("$", arg_list[i], 1) == 0)//If it sees a $ before a word it attempts to grab the environment described (e.g. $HOME will expand to the home directory)
			{
				arg_list[i] = strtok(arg_list[i], "$");
				if(getenv(arg_list[i]) != 0)
					arg_list[i] = getenv(arg_list[i]);
			}
		}
		for(int t=1; t<commandcount; t++)
			{
				
				if (strncmp("=", arg_list[t], 1) == 0) // If there is a '=' then it knows to apply the RHS to the LHS, which needs to be an environment var
					{
						strcpy(arg_list[t], arg_list[t+1]);
						for(int p =t+2; p<commandcount; p++)
							{ 
								strcat(arg_list[t]," ");
								strcat(arg_list[t],arg_list[p]);
							}
						setenv (arg_list[t-1], arg_list[t], 1);
						goahead = -1;
					}
				else if (strcmp ("|", arg_list[t]) == 0) //If there is a pipe, send the command to "domanycommands" which handles piping
					{
						domanycommands(arg_list, environment, t, commandcount);
						goahead = -1;
						break;
					}
				
				else{
					if (strcmp (">", arg_list[t]) == 0 || strcmp ("<", arg_list[t]) == 0)//If theres like a lot of alligators, yell at them.
						{
						if(t+1 != commandcount){
							for(int many=t+1; many<commandcount; many++)
								{
									if (strcmp (">", arg_list[many]) == 0 || strcmp ("<", arg_list[many]) == 0)
										{
											cout <<"That command doesn't make sense, dood." << endl;
											goahead = -1;
											break;
										}
								}
						}}
					}
			}
		if( strcmp("quit", arg_list[0]) == 0 ){
			works = write_history ("history.txt");
			if(works != 0){cout<<"Error in writing history file."<<endl;}
			break;} //quits the program
		else if (goahead != -1)
		{
			cpid = fork();
			if(cpid == 0)
				{
					arg_list[commandcount] = NULL;
					findanddo(arg_list,environment,commandcount);
				}
			else if (cpid < 0) //if the status is <0 there was a forking error
				exit(EXIT_FAILURE); 
			else if (cpid > 0) // This is the parent process.  Wait for the child to complete.
				waitpid (cpid, NULL, 0);
			else;
		}
		goahead =0;
	}
}
