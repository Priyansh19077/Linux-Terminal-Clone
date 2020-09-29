#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
char *initial_directory;
FILE *history_read;
int count = 1;
void print(char *file_name, int flag) {
    char *path = malloc(1000 * sizeof(char));
    initial_directory = malloc(1000 * sizeof(char));
    getcwd(initial_directory, 1000);
    strcpy(path, initial_directory);
    strcat(path, "/");
    strcat(path, file_name);
    history_read = fopen(path, "r");
    // printf("%s\n",path);
    if (history_read == NULL) {
        printf("%s is NOT a valid readable file\n", file_name);
        return;
    }
    char *history1 = malloc(1000 * sizeof(char));
    while (fgets(history1, 1000, history_read) != NULL)
    {
        if (flag == 1)
        {
            printf("%s", history1);
        }
        else if (flag == 2)
        {
            printf("%d %s", count++, history1);
        }
        else if (flag == 3)
        {
            history1[strlen(history1) - 1] = '\0';
            printf("%s$\n", history1);
        }
    }
    fclose(history_read);
}
void printing(char *args, char *args1)
{
    if (!strcmp(args, ""))
        print(args1, 1);
    else if (!strcmp(args, "-E"))
        print(args1, 3);
    else if (!strcmp(args, "-n"))
        print(args1, 2);
}
int main(int a, char**args) {
    int index = 0;
    int n = strlen(args[1]);
    char *string = malloc(1000 * sizeof(char));
    string[0] = '\0';
    int i = 0;
    while (i <= n)
    {
        if (i == n || args[1][i] == ' ')
        {
            printing(args[0], string);
            string[0] = '\0';
            i++;
            index = 0;
        }
        else
        {
            string[index++] = args[1][i++];
            string[index] = '\0';
        }
    }
    return 0;
}