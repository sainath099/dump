//program to define the server main function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

int main()
{	
   	load();		        //calling the function leadDAta of server class
   	printf("in1");
	ToCreateSocket();			//calling the function createSocket() of the server class to create the socket
	ToBindSocket();			//calling the function bindSocket to bind the socket
	ToListen(); 			//calling the function listenTo of the server class 
	ToAcceptConnections() ;		//calling the acceptConnection of the server class
}
