#include <stdio.h>
#include <time.h>
#include<string.h>
#include <errno.h>
#include<unistd.h>
#include<stdlib.h>
extern int errno ;

int main(int a, char**args) {

    char * current_directory = malloc(100 * sizeof(char));
    getcwd(current_directory, 100);
    if (current_directory == NULL)
    {
        printf("%s\n", "We could not get the directory of the file you are deleting !!!" );
        return 0;
    }
    if (!strcmp(args[2], current_directory))
    {
        if (!strcmp(args[1], "history.txt")
                || !strcmp(args[1], "shell.c")
                || !strcmp(args[1], "mkdir.c")
                || !strcmp(args[1], "ls.c")
                || !strcmp(args[1], "cat.c")
                || !strcmp(args[1], "date.c")
                || !strcmp(args[1], "rm.c")
                || !strcmp(args[1], "rm.c")
                || !strcmp(args[1], "rm")
                || !strcmp(args[1], "mkdir")
                || !strcmp(args[1], "ls")
                || !strcmp(args[1], "date")
                || !strcmp(args[1], "cat")
                || !strcmp(args[1], "shell"))
        {
            printf("%s\n", "You are not permitted to delete the code files of the project!!!");
            return 0;
        }
    }
    if (!strcmp(args[0], ""))
    {

        int status = unlink(args[1]);
        if (!status)
        {
            //deleted successfully
        }
        else
        {
            printf("Error in deleteing: %s\n", strerror(errno));
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
                        printf("Error in deleteing: %s\n", strerror(errno));
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
            printf("Error in deleteing: %s\n", strerror(errno));
            return 0;
        }

    }
    return 0;
}