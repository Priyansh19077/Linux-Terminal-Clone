#include <stdio.h>
#include <time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main(int a, char**args) {

	if (!strcmp(args[0], ""))
	{
		int status = unlink(args[1]);
		if (!status)
		{
			//deleted successfully
		}
		else
		{
			printf("%s\n", "Some error occured in deleting the file.");
		}
	}
	if (!strcmp(args[0], "-i"))
	{
		while (1)
		{
			printf("%s\n", "Are you sure you want to delete this file? (Y/N)");
			char *ch = malloc(100 * sizeof(char));
			scanf("%s", ch);
			if (!strcmp(ch, "Y") || !(strcmp(ch, "N")))
			{
				if (!strcmp(ch, "Y"))
				{
					int status = unlink(args[1]);
					if (!status)
					{
						//deleted successfully
						return 0;
					}
					else
					{
						printf("%s\n", "Some error occured in deleting the file.");
						return 0;
					}
				}
				else
					return 0;
			}
			else
			{
				printf("%s\n", "Please enter a valid choice (Y/N)");
			}
		}
	}
	if (!strcmp(args[0], "-v"))
	{

		int status = unlink(args[1]);
		if (!status)
		{
			//deleted successfully
			printf("removed %s\n", args[1]);
			return 0;
		}
		else
		{
			printf("%s\n", "Some error occured in deleting the file.");
			return 0;
		}

	}
	return 0;
}