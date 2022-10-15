#include <stdbool.h>
FILE * openr(char * filename)
{
	FILE *fp;
    if(strcmp(filename,"production")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/production.txt","r");
	}
	else if(strcmp(filename,"marketing")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/marketing.txt","r");
	}
	else if(strcmp(filename,"testing")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/marketing.txt","r");
	}
	else
	{
		fp=NULL;
	}                               
    if (fp == NULL) 
    {
        printf("The file didn't open.\n");
        return NULL;
    }
    return fp;
}
FILE * openw(char * filename)
{
	FILE *fp;
    if(strcmp(filename,"production")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/production.txt","w");
	}
	else if(strcmp(filename,"marketing")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/marketing.txt","w");
	}
	else if(strcmp(filename,"testing")==0)
	{
		fp=fopen("/home/kali/Desktop/remote_phonebook/db/marketing.txt","w");
	}
	else
	{
		fp=NULL;
	}                               
    if (fp == NULL) 
    {
        printf("The file didn't open.\n");
        return NULL;
    }
    return fp;
}

FILE * openapp(char * filename)
{
    FILE * f1;
    if(strcmp(filename,"production")==0)
	{
		f1=fopen("/home/kali/Desktop/remote_phonebook/db/production.txt","a");
		return f1;
	}
	else if(strcmp(filename,"marketing")==0)
	{
		f1=fopen("/home/kali/Desktop/remote_phonebook/db/marketing.txt","a");
		return f1;
	}
	else if(strcmp(filename,"testing")==0)
	{
		f1=fopen("/home/kali/Desktop/remote_phonebook/db/testing.txt","a");
		return f1;
	}
	else if(strcmp(filename,"public group")==0)
	{
		f1=fopen("/home/kali/Desktop/remote_phonebook/db/public group.txt","a");
		return f1;
	}
    return NULL;
}

int addintofile(char* name,char* phone,char* filename)
{
      FILE * fp;
      fp=openapp(filename);
      if(fp==NULL)
      {
      	printf("dd");
      }
      else
      {
      	fputs(name,fp);
      	fputs(",",fp);
      	fputs(phone,fp);
      	fputs("\n",fp);
      	fclose(fp);
      	return 1;
      }
      fclose(fp);
      return 0;
}


int addgroup(char * filename)
{
      FILE * fp;
      char path[1024]="";
      char fname[100]="";
      int i=0;
      for (i=0; *(filename+i) != '\0'; i++)
      {
        fname[i] = *(filename+i);
      }
      strcpy(path,"/home/kali/Desktop/remote_phonebook/db/");
      strcat(path,fname);
      strcat(path,".txt");
      fp=fopen(path,"w");
      if(fp==NULL)
      {
      	return 0;
      }
      fclose(fp);
      return 1;
}

int removegroup(char * filename)
{
      char path[1024]="";
      char fname[100]="";
      int i=0;
      for (i=0; *(filename+i) != '\0'; i++)
      {
        fname[i] = *(filename+i);
      }
      strcpy(path,"/home/kali/Desktop/remote_phonebook/db/");
      strcat(path,fname);
      strcat(path,".txt");
      if (remove(path) == 0)
      return 1;
      return 0;
}

int removecontact(char * name, char * filename)
{
	  FILE * fp1,* fp2;
      char path1[1024]="";
      char path2[1024]="";
      char fname[100]="";
      int i=0;
      for (i=0; *(filename+i) != '\0'; i++)
      {
        fname[i] = *(filename+i);
      }
      strcpy(path1,"/home/kali/Desktop/remote_phonebook/db/");
      strcpy(path2,"/home/kali/Desktop/remote_phonebook/db/");     
      strcat(path1,fname);
      strcat(path2,"temp_");
      strcat(path2,fname);
      strcat(path1,".txt");
      strcat(path2,".txt");
      fp1=fopen(path1,"r");
      fp2=fopen(path2,"w");
      if (fp1 == NULL || fp2 == NULL)
	  {
		return 0;
	  }
	  bool keep_reading = true;
	  do 
	  { 
	  	char buffer[1024];
		fgets(buffer, 1024, fp1);
		if (feof(fp1)) 
		keep_reading = false;
		else if (strncmp(buffer, name,strlen(name))!= 0)
		  fputs(buffer, fp2);

	  } while (keep_reading);
	  fclose(fp1);
	  fclose(fp2);
	  remove(path1);
	  rename(path2,path1);
	  return 1;
}
      
      
	
