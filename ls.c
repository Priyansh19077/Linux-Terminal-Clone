#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h> 
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
int main(int a, char**args){
	// char * current_directory=malloc(100*sizeof(char));
	// getcwd(current_directory,100);
	struct dirent *de;   
    DIR *dr = opendir("."); 
    if (dr == NULL)  
    { 
       	printf("Could not open current directory" ); 
     	return 0; 
    }  
    // printf("%s\n",args[0]);
    while ((de = readdir(dr)) != NULL) 
    {
        if(!strcmp(args[0],"-l"))   //show the long format
        {
            printf("%s\n",de->d_name);
            printf("details:\t");
            struct stat sbuf;
            stat(de->d_name,&sbuf);
            if(sbuf.st_size==0)   //Check for empty file
                 printf("d");
            if(sbuf.st_mode & S_IREAD)
                printf("r");
            if(sbuf.st_mode & S_IWRITE)
                printf("w");
            if(sbuf.st_mode & S_IEXEC)
                printf("x");
                  //Print the size
            printf("\t\t%ld",sbuf.st_size); 
            printf("\t%s",ctime(&sbuf.st_ctime)); 
        }
        else if(!strcmp(args[0],"-A"))  //ignore the '.' and ".." //default
        {
            if(!strcmp(de->d_name,".") || !strcmp(de->d_name,".."))
                continue;
            printf("%s\n", de->d_name); 
        }
        else if(!strcmp(args[0],"")) //normal without any flag
        {
            printf("%s\n", de->d_name);  
        }
    }
    closedir(dr);     
	return 0;
}
