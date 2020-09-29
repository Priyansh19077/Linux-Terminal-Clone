#include <stdio.h>
#include <time.h>
#include<string.h>
int main(int a, char**args) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if(!strcmp(args[0],""))
    {
       printf("%s\t","local time");
 	   printf("%s", asctime(tm));
	}
	if(!strcmp(args[0],"-u"))
	{
    	struct tm *ptm = gmtime ( &t ); // Find out UTC time
		time_t utctime = mktime(ptm); // Get UTC time as time_t
		printf("%s\t","UTC time");
		printf("%s",ctime(&utctime));
	}
    return 0;
}