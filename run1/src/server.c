/*  program to define the class server   */


//#include <server.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
int sockfd;
struct sockaddr_in servaddr ;
struct sockaddr_in cliaddr ;
int slen = 0 ,connectfd = 0, mlen = 0 ;
pid_t pid ;

void load()
{
	FILE *fp;
    fp=fopen("home\\Sai Nath Reddy\\run1\\db\\authentication.txt","r");
	if(fp==NULL)
	{
		printf("authentication.txt doesn't exist");
		exit(0);
	}
	fclose(fp);
}
	



//function to create socket 

int ToCreateSocket()
{
            slen=sizeof(struct sockaddr_in);
            memset(&servaddr,0,slen);
            memset(&cliaddr,0,slen);

            servaddr.sin_family = AF_INET; //To use Internet addressing family
            servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
            servaddr.sin_port = htons(PORT);


            sockfd=socket(AF_INET, SOCK_STREAM, 0);                                                                     //creating the socket
            if(sockfd < 0)
            {
              printf("Socket creation has not been done");
            }
            else
            {
            	printf("Inside server socket,%d",sockfd);
            }
            return 0;
}



//function to bind the socket
int ToBindSocket()
{
            int ret;
            ret=bind(sockfd, (struct sockaddr *)&servaddr, slen);                                                       //binding the socket
            if(ret < 0)
            {
                    printf("Binding has not been done");
             }
             return 0;
}



//function to call listening to the port 8028
int ToListen()
{
            int ret;
            ret=listen(sockfd, 5);                                                                                      //listening to the port 8028
            if(ret< 0)
            {
                    printf("Socket is not Listening");
            }
            return 0;
}



//function to acceptconncetion and and concurrency by using child process
void ToAcceptConnections()
{
	while(1)
	{
		//connectfd=accept(sockfd,(struct sockaddr*)&servaddr,(socklen_t *)&slen);
		if(connectfd < 0)
		{
			printf("Conncetion is not established");
		}
		pid = fork();                                                                                               //creating the child process   
	    if (pid == 0)
	    {
	    	char *filename = "" ;
	    	char * type =ToAuthenticateUser();                                //calling the authenticate function to check the username is authentic user
			char type1[20];        
			if( strcmp("admin",type)!=0 && strcmp(type,"")!=0)
			{
				strcpy(type1,"authenticated user") ;
			}
			else if(strcmp(type,"")==0)
			{
				strcpy(type1,"anonymous user") ;
			}
			else if(strcmp(type,"admin")==0)
			{
				strcpy(type1,"admin") ;
			}
			mlen=send(connectfd,type1,strlen(type1),0);                             		//sending the type of user to the client
            
            while(1)
            {
            	char * recvdata = SToRecvData();                                                   	//calling the function to receive data
				if(strcmp(type1,"authenticated user")==0)													//checking the user is authenticated
				{
					AuthenticatedUserFunctionalities(recvdata,filename,type);		//calling the funtion to perform authenticated user functionalities
                }
                if(strcmp(type1,"anonymous user")==0)
                {                                                            //checking whether the user id anonymous
                	AnonymousFunctions(recvdata,filename);					//calling the function to perform anonymous user functionalities
                }
                if(strcmp(type1,"admin"))
                {														 //checking whether the user is admin
                	AdminFunction(recvdata,filename);					//calling the function to perform admin functionalities
                }
            }
		}
        signal(SIGCHLD,SIG_IGN);                                                                                	//signal to avoid Zombie process
	    close(connectfd);
	}	
}


char * AuthenticatedUserFunctionalities(char *recvdata,char *filename ,char * type)
{
      char * command="";
      char *input1,*input2;
      char subcommand[256]="";
      for (int i=0; *(recvdata+i) != '\0'; i++)
      {
        subcommand[i] = *(recvdata+i);
      }
      command= strtok(subcommand," ");
      input1=strtok(NULL,",");
      input2=strtok(NULL,",");
    
	if(strcmp(command,"ADD")==0)
	{
		int res=ToAddData(input1,input2,filename);						//calling the adddata function of user class
		if(res==1)
		{
			char * positive="Contact added" ;
			send(connectfd,positive,strlen(positive),0);     						//sending the message to the client
			return filename;
        }
		else
		{
			char * negative="The user can't add the data to the public group";
			send(connectfd,negative,strlen(negative),0);
		}
	}
	else if(strcmp(command,"chgrp")==0)
	{
		filename=ToChgrp(input1,type);
		if(strcmp(filename,"no")==0)
		{
			char neg[70]="The user doesnt belong to the group";
			send(connectfd,neg,strlen(neg),0);
		}
		else
		{
			char pos[20]="Group changed" ;
			send(connectfd,pos,strlen(pos),0);
			return filename ;
        }
	}
            else if(strcmp(command,"rm")==0)
            {                                   				                //checking if the command is remove
                  char * res = "" ;
                  res = ToRemoveContact(input1,filename);                              				//calling the user function to remove the contact
                  if(strcmp(filename,res)==0)
                  {
      	            char * pos = "Contact removed " ;
            	    send(connectfd,pos,strlen(pos),0);
            	    res=filename;
		      		return res ;
                  }
                  else
                  {
                  	char * neg="Entered user is not present";
                    send(connectfd,neg,strlen(neg),0);
                    res=filename;
		      		return res ;
                  }
            }
		return "";
}





//function to implement admin functionalities

void AnonymousFunctions(char * recvdata ,char * filename)
{
      char * command="";
      char *input1,*input2;
      char subcommand[256]="";
      for (int i=0; *(recvdata+i) != '\0'; i++)
      {
        subcommand[i] = *(recvdata+i);
      }
      command= strtok(subcommand," ");
      input1=strtok(NULL,",");
      input2=strtok(NULL,",");
      if(strcmp(command,"ADD")==0)
      {                                                           					//checking if the command is ADD
   	   	 filename="public group";
         int res=ToAddData(input1,input2,filename);
         if(res == 1)
         {
      	   char * positive = "Contact added" ;
           send(connectfd,positive,strlen(positive),0);
         }
         else
         {
         	char * negative="Contact is not added" ;
            send(connectfd,negative,strlen(negative),0);
         }
     }
}




//function to implement admin Function

void AdminFunction(char * recvdata,char * filename)
{
      char * command="";
      char *input1,*input2,*input3;
      char subcommand[256]="";
      int i=0;
      for (i=0; *(recvdata+i) != '\0'; i++)
      {
        subcommand[i] = *(recvdata+i);
      }
      command= strtok(subcommand," ");
      input1=strtok(NULL,",");
      input2=strtok(NULL,",");
      input3=strtok(NULL,",");
      if(strcmp(command,"addgrp")==0)
      {
            filename = input1;
            int res = addgroup(filename);
            if(res==1)
            {
             	char * positive = "Group added " ;
                 send(connectfd,positive,strlen(positive),0);
            }
            else
            {
            	char * negative="Error while adding the group " ;
            	send(connectfd,negative,strlen(negative),0);
            }
      }
      else if(strcmp(command,"rmgrp")==0)
      {
      	filename = input1 ;
      	int res = removegroup(filename);									//calling the function remove group to remove the group
      	
		if(res==1)
		{
      		char positive []= "Group removed " ;
      	      send(connectfd,positive,strlen(positive),0);
      	}
      	else{
      		char negative[]="No group is present in that name" ;
      	      send(connectfd,negative,strlen(negative),0);
      	}
      }
      else if(strcmp(command,"ADD")==0)
      {
            filename = input3;
            int res = addintofile(input1,input2,filename);
            if(res==1)
            {
                  char * positive = "";
                  positive="contact added to the given group";	
                  send(connectfd,positive,strlen(positive),0);
            }
            else
            {
            	char * negative="Group doesn't exist ,Add the group to add the data" ;
                send(connectfd,negative,strlen(negative),0);
            }
      }
}





//function to receive data
/*char * SToRecvData()
{
        char * res ="";
        char recvdata[1024] ;
        memset(recvdata,0,1024);
        recv(connectfd , recvdata,1024 , 0);
        if(strcmp(recvdata,"bye")==0 || strcmp(recvdata,"Bye")==0)
        {                  
                close(connectfd);
                exit(0);
        }
        res = recvdata;
        return res;
}*/

char * SToRecvData()
{
        //char recvdata[1024]="" ;
        //memset(recvdata,0,1024);
        char * res ="";
        recv(connectfd ,res,1024 , 0);
        //strcpy(recvdata,"698998");
        if(strcmp(res,"bye")==0 || strcmp(res,"Bye")==0)
        {                  
                close(connectfd);
                exit(0);
        }
        //res = recvdata;
        //printf("%s,%s\n",recvdata,res);
        return res;
}



//function to authenticate user
char * ToAuthenticateUser()
{
        char *res = "";
        char receivedata[1024];
        memset(receivedata,0,1024);
        recv(connectfd ,receivedata,1024 , 0);
        printf("%s",receivedata);
        if(strcmp(receivedata,":")==0)
        {
        	return res;
        }
        char username[50],password[50] ;
        char recvdata[1024];
        strcpy(recvdata,receivedata);
    	strcpy(username,strtok(recvdata,":"));
    	strcpy(password,strtok(NULL,"\0"));
        FILE *fp;
    	char * line;
    	int size = 1024;
    	line = (char *)malloc(1024);
    	fp=fopen("/home/kali/Desktop/remote_phonebook/db/authentication.txt","r");
    	if(fp!=NULL)
    	{                                                                                //checking whether the file is opened
         	while(getline(&line,&size,fp) && !feof(fp))
         	{
         		char t[1024];
         		strcpy(t,line);
         		t[strlen(t)-1]='\0';
				char u[50] ,p[50] ;
				strcpy(u,strtok(t,":"));
				if(strcmp(u,username)==0)
				{
    				strcpy(p,strtok(NULL,":"));
    				if(strcmp(p,password)==0)
    				{
    					res= u;
    					break;
    				}
    			}	
			}
    	} 
    	fclose(fp);
    	free(line);
        return res;
}



