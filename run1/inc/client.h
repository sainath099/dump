//program to have a header file for client class
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
void Client();
int ToGetSockfd();				//to get sock id
char *ToGetCredentials();			//to get credentials
int ToServerConnect( );				//to connect to the server
int ToSendData(char * input);			//to send data to the server
char * CToRecvData();				//to receive data from the server
char * ToGetUserCommands(char * type);		//to get user subcommands
void ToDisplayRecvData(char * recvData);		//to display records from the server
int ToCloseClientConnections();			//to close the client connections

        	
