//program to define the class user
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <user.h>
#include "open.h"
	


//function to add data to the phonebook 
int ToAddData(char * input1 ,char * input2,char * filename)
{
      int r=addintofile (input1 ,input2,filename);
      return r;
}


//function to add data to the phonebook 
int ToAdminAddData(char * input1 ,char * input2,char * filename)
{
      int r = addintofile(input1 ,input2,filename);
      return r;
}



//function to remove contact from the phonebook
char * ToRemoveContact(char * input,char * filename)
{
      char * res="";
      int result=removecontact(input, filename);
      if(result==1)
      {
      	res=filename;
      }
      return res;
}




//function to list the data with the substring and returns a vector oof string
/*vector<string> User::ToListData(string input,string filename)
{
      ifstream infile ;
      vector<string> listedContact;
      string line = "";
      if(filename!=""){

            infile.open("/home/cguser11/phonebook_management/db/"+filename + ".txt");
            listedContact.push_back("The contacts in the " + filename + " group\n");
            if(infile.is_open()){
            	while(getline(infile,line)){
                  	string name ,phonenumber ;
                        stringstream ss(line);
                        getline(ss,name,',');
                        getline(ss,phonenumber,',');
                        if(name != "" && phonenumber !=""){
                        	if(name.substr(0,input.size()) == input){
                              		listedContact.push_back("Name :" + name + "\t\tPhonenumber :" + phonenumber + "\n");
                              }
                        }
            	}
     		}
    		infile.close();
     	}
      else{
      	infile.open("/home/cguser11/phonebook_management/db/public group.txt");
            if(infile.is_open()){
            	listedContact.push_back("The contacts in the public group\n");
                  while(getline(infile,line)){
                  	string name ,phonenumber ;
                        stringstream ss(line);
                        getline(ss,name,',');
                        getline(ss,phonenumber,',');
                        if(name != "" && phonenumber != ""){
                        	if(name.substr(0,input.size()) == input){
                        	      	listedContact.push_back("Name :" + name + "\t\tPhonenumber :" + phonenumber + "\n");
                              }
                        }
                  }
             }
     infile.close();
     }
     return listedContact;
}*/



//function to change the group
char * ToChgrp(char * input,char *type)
{
	    char *res = "no";
        char grp[40];
        memset(grp,0,40);
        strcpy(grp,input);
        grp[strlen(input)]='\0';
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
         		char *tok;
         		tok=strtok(t,":");
         		if(strcmp(tok,type)==0)
         		{
		     		tok=strtok(NULL,":");
		     		tok=strtok(NULL,":");
		     		while(tok!=NULL)
		     		{
		     			if(strcmp(tok,grp)==0)
		     			{
		     				res=grp;
		     				break;
		     			}
		     			tok=strtok(NULL,":");
		     		}
		     		break;
		     	}
         	}
    	} 
    	fclose(fp);
    	free(line);
        return res;
}



//function to add group to the directory
int ToAddGrp(char * filename)
{
	return (addgroup(filename));
}



//function to remove group from the directory
int ToRemoveGrp(char * filename)
{
	return (removegroup(filename));
}

