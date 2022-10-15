//program to define the class client


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
//#include <limits.h>
#include <string.h>
#include <arpa/inet.h>
//#include <termios.h>
#include <signal.h>
#include <client.h>
int sockfd;                                             
struct sockaddr_in servaddr;
int portnumber,slen,mlen,connectfd;
char ip_address[130];

#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8028
      
void Client()
{
	connectfd = 0;
	mlen = 0 ;
	portnumber =0 ;
    memset(&servaddr,0,slen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
    servaddr.sin_port = htons(PORT);
    slen=sizeof(servaddr);
    sockfd=socket(AF_INET, SOCK_STREAM, 0);										
    if(sockfd < 0)
    {
	      //fputs("Socket can't be created ",stderr);
	      printf("Socket can't be created ");
          exit(EXIT_FAILURE);
    }
}


//function to get socket id
int ToGetSockfd()
{
	return sockfd ;
}


//function to credentials from the User
char *ToGetCredentials()
{
      char *res ="";
      char uName[50] ;
      char password[50];
      printf("Enter the Username :") ;
      fgets(uName,50,stdin);
      if(strcmp(uName,"\n")==0)
      {
      	strcpy(uName,"");
      }
      else
      {
        uName[strlen(uName)-1]='\0';  
      }
      printf("Enter the password :") ;
      fgets(password,50,stdin);
      if(strcmp(password,"\n")==0)
      {
	      strcpy(password,"");
      }
      else
      {
        password[strlen(password)]='\0';  
      }
      char concat[1024]="";
      strcat(concat,uName);
      strcat(concat,":");
      strcat(concat,password);
      res=concat;
      return res;
}


//function to connect to the server
int ToServerConnect()
{
	printf("before connect,ToServerConnect\n");
	connectfd=connect(sockfd,(struct sockaddr *)&servaddr,slen);
	printf("%d,ToServerConnect\n",connectfd);
    if(connectfd < 0)
    {
    	printf("Socket can't be created ");
        exit(EXIT_FAILURE);
    }
    return connectfd;
}


//function to senddata from the client
int ToSendData(char * str)
{
	printf("inside:%s",str);
	send(sockfd,str,strlen(str),0);
    if(strcmp(str,"bye")==0||strcmp(str,"Bye")==0)
    {												//checks for bye if bye close client conncetion
      	ToCloseClientConnections();
    }
	return 0 ;
}



// function to receive the data from the server
/*char * CToRecvData()
{      
      char * res ="";
      char recvdata[1024] ;
      memset(recvdata,0,1024);
      mlen=recv(connectfd , recvdata,1024 , 0);
      if(mlen==0)
      {
      	ToCloseClientConnections();
      }
      res = recvdata;
      return res;
}*/
char * CToRecvData()
{
        //char recvdata[1024]="" ;
        //memset(recvdata,0,1024);
        char * res ="";
        mlen=recv(connectfd ,res,1024 , 0);
        //strcpy(recvdata,"698998");
        if(mlen==0)
        {                  
                ToCloseClientConnections();
        }
        //res = recvdata;
        //printf("%s,%s\n",recvdata,res);
        return res;
}




//function to get the subcommands from the user
char * ToGetUserCommands(char * type)
{
	while(1)
	{
      	    char subcommand[200]="";
            printf("\nEnter the subcommand :") ;
            fgets(subcommand,200,stdin);
            subcommand[strlen(subcommand)-1]='\0';
            char *copysubcommand="";
            copysubcommand = (char *)malloc(200);
            memset(copysubcommand,0,200);
            strcpy(copysubcommand,subcommand);
	    	if(strcmp(type,"authenticated user")==0)
	    	{			
            	  char * command="";
            	  char *input1,*input2;
            	  command= strtok(subcommand," ");
            	  input1=strtok(NULL,",");
                  input2=strtok(NULL,",");
                  if(strcmp(command,"ADD")==0)
                  {											
                  	if(input1!=NULL&&input2!=NULL)
                  	{
                        	return copysubcommand;
                    }
                    else
                    {
                    	printf("ADD command should have two fields\n");
                        continue;
					}
                 }
                 else if(strcmp(command,"rm")==0)
                 {											//checks for remove command
                   	if(input1!=NULL && input2 == NULL)
                   	{
                        	return copysubcommand ;
                    }
                    else
                    {
                        printf("Remove command should have only one field"); 
                        continue;
                    }
                 }
                 else if(strcmp(command,"list")==0)
                 {											//checks for list command
                   	if(input1!=NULL && input2 == NULL)
                   	{
                   		return copysubcommand ;
                    }
                    else
                    {
                    	printf("List command should have only one field");
                        continue;
                    }
                }
                else if(strcmp(command,"chgrp")==0)
                {											//checks for the chgrp command
                   	if(input1!=NULL && input2 == NULL)
                   	{
                   		return copysubcommand ;
                   	}
                   	else
                   	{
                   		printf("Enter only Groupname");
                   		continue;
                    }
                }
                else if(strcmp(command,"Bye")==0||strcmp(command,"bye")==0)
                {	
                   	if(input1==NULL && input2==NULL)
                   	{
                   		return copysubcommand ;
                    }
                    else
                    {
                    	printf("No inputs with bye/Bye");
                        continue;
                    }
                }
                else
                {
                	printf("You can only use ADD,rm,list,chgrp and bye/Bye subcommands");
                	continue;
                }
	      }
	      
	      if(strcmp(type,"admin")==0)
	      {													//checks for the type admin
            	  char * command;
            	  char *input1,*input2,*input3;
            	  command= strtok(subcommand," ");
            	  input1=strtok(NULL,",");
                  input2=strtok(NULL,",");
                  input3=strtok(NULL,",");
                  if(strcmp(command,"addgrp")==0)
                  {											//checks for the ADD command
            	      if(input1!=NULL && input2==NULL)
            	      {
                  	      return copysubcommand ;
                      }
                      else
                      {
                          printf("Enter groupname only");
                          continue;
                      }
                   }
                   else if(strcmp(command,"rmgrp")==0)
                   {											//checks for the remove command
                   		if(input1!=NULL && input2 ==NULL)
                   		{
                        	return copysubcommand ;
                        }
                        else
                        {
                        	printf("Enter groupname only");
							continue;
                        }
                    }
                    else if(strcmp(command,"ADD")==0)
                    {											//checks for ADD command
                  		if(input1!=NULL && input2!=NULL && input3!=NULL)
                  		{
                        	return copysubcommand;
                        }
                        else
                        {
                        	printf("Provide three inputs name,phonenumber,filename ");
                            continue;
                        }
                    }
                    
                    else if(strcmp(command,"Bye")==0||strcmp(command,"bye")==0)
                	{									//checks for bye command 
		               	if(input1==NULL&&input2==NULL)
		               	{
		               		return copysubcommand ;
		                }
		                else
		                {
		                	printf("No inputs with bye/Bye");
		                    continue;
		                }
		            }
                    else
                    {
                     	printf("Enter addgrp , rmgrp or ADD  subcommand only");
                        continue;
                    }
               }
			   if(strcmp(type,"anonymous user")==0)
			   {											//checks for anonymous user
		              char * command="";
		        	  char *input1,*input2;
		        	  command= strtok(subcommand," ");
		        	  input1=strtok(NULL,",");
		              input2=strtok(NULL,",");
		              if(strcmp(command,"ADD")==0)
		              {											
				          	if(input1!=NULL&&input2!=NULL)
				          	{
				                	return copysubcommand;
				            }
				            else
				            {
				            	printf("ADD command should have two fields\n");
				                continue;
							}
		              }
		              else if(strcmp(command,"Bye")==0||strcmp(command,"bye")==0)
		              {									//checks for bye command 
				           	if(input1==NULL&&input2==NULL)
				           	{
				           		return copysubcommand ;
				            }
				            else
				            {
				            	printf("No inputs with bye/Bye");
				                continue;
				            }
				      }
		              else
		              {
		               	printf("User should provide only ADD subcommand") ;
		                 continue;
		              }
		       }
	}
	printf("\n");
    return "" ;
}



//function to display data received from server
void ToDisplayRecvData(char * recvData)
{
	printf("%s",recvData);
}



//function to close connection from the server
int ToCloseClientConnections()
{
      close(sockfd);
      exit(0);
}



