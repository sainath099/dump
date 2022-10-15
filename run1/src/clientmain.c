//program to define the server main function
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"
int sockid ;
void signalHandler(int signal)
{
        if(signal==SIGINT)
        {
                send(sockid,"bye",3,0);
                exit(0);
        }
}

//main function to execute client class

int main () 
{
        signal(SIGINT,signalHandler);						//signal to cut the client from server
        char * recvdata,* credentials,* commands;
        Client();								//creating a object of client
        sockid=ToGetSockfd();						//calling the getsockfd of client class
        credentials=ToGetCredentials();		//calling the getcredentials functions of client class
        printf("%s,aftercredentials\n",credentials);
        int c=ToServerConnect() ;				//calling the serverconnect function to connect to the server
        printf("%d,inclientmain\n",c);
        ToSendData(credentials);						//sending the credentials to server 
        recvdata=CToRecvData();			//receiving the message from the server using recvData function
        char * type =recvdata ;							
        ToDisplayRecvData(recvdata);					//calling the funtion to display the data
        while(1)
        {
                commands = "";
                commands=ToGetUserCommands(type) ;		//calling the function to get the usercommands
                if(strcmp("",commands)!=0)
                {
               	   ToSendData(commands);					//sending the user commands to the server
                   recvdata = CToRecvData();				//receiving the data from the server
                   ToDisplayRecvData(recvdata);			//displaying the received data from the server
                }
                else
                {
                        printf("Subcommand can't be Null");
                        continue;
                }
        }
        return 0;
}

