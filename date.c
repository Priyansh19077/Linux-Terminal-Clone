#include <stdio.h>
#include <time.h>
#include<string.h>
int main(int a, char**args) {

	if (!strcmp(args[0], ""))
	{
		time_t time1;
		struct tm *information;
		char string[80];
		time( &time1 );
		information = localtime( &time1 );
		strftime(string, 80, "%a %b %d %H:%M:%S %Z %Y", information);
		printf("%s\n", string);
	}
	if (!strcmp(args[0], "-u"))
	{
		time_t time1;
		struct tm *information;
		char string[80];
		time( &time1 );
		information = gmtime( &time1 );
		strftime(string, 80, "%a %b %d %H:%M:%S UTC %Y", information);
		printf("%s\n", string);
	}
	if (!strcmp(args[0], "-R"))
	{
		time_t time1;
		struct tm *information;
		char string[80];
		time( &time1 );
		information = localtime( &time1 );
		strftime(string, 80, "%a, %b %d %H:%M:%S %z", information);
		printf("%s\n", string);
	}
	return 0;
}