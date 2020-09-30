#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <errno.h>
#include <dirent.h>
char *current_directory;
char *initial_directory;
int initial_size;
int position;
extern int errno ;
FILE *history_write;
FILE *history_read;
char *take_input()
{
	int initial_size = 1000;
	char *string = malloc(sizeof(char) * initial_size);
	if (string == NULL)
	{
		//could not allocate the memory
		printf("%s\n", "Could not allocate memory!! Try again");
		string[0] = '\0';
		return string;
	}
	fgets(string, initial_size, stdin);
	int n = strlen(string);
	n--;
	while (n > 0) //handling extra spaces after the command.
	{
		if (string[n] == '\n' || string[n] == ' ')
			string[n--] = '\0';
		else
			break;
	}
	return string;
}
void print_history1()
{
	char *path = malloc(1000 * sizeof(char));
	strcpy(path, initial_directory);
	strcat(path, "/history.txt");
	history_read = fopen(path, "r");
	char *history1 = malloc(1000 * sizeof(char));
	int count = 1;
	while (fgets(history1, 1000, history_read) != NULL)
	{
		printf("%d %s", count++, history1);
	}
	fclose(history_read);
}
void delete_offset(int x)
{
	char *path = malloc(1000 * sizeof(char));
	strcpy(path, initial_directory);
	strcat(path, "/history.txt");
	history_read = fopen(path, "r");
	char *history1 = malloc(1000 * sizeof(char));
	int count = 0;
	// printf("%d\n",x);
	char histories[10000][100];
	while (fgets(history1, 1000, history_read) != NULL)
	{
		strcpy(histories[count], history1);
		count++;
		// printf("%d %s", count++, history1);
	}
	fclose(history_read);
	history_write = fopen(path, "w");
	fputs("", history_write);
	fclose(history_write);
	history_write = fopen(path, "a");
	for (int i = 0; i < count; i++)
	{
		if (i != x - 1)
		{
			// printf("%s\n",histories[i]);
			fputs(histories[i], history_write);
			// fputs("\n",history_write);
		}
	}
	fclose(history_write);
	return;
}
int handle_internal_command(char *command, char *flag, char *args)
{

	if ((!strcmp(command, "exit"))) //exit command
		return 10;
	if (!strcmp(command, "history")) //history command
	{
		//mainitaining history for not just when the program is running but overall
		if (strcmp(args, ""))
		{
			printf("%s\n", "No arguments supported with this command!!!");
			return 1;
		}
		if ((!strcmp(flag, "-c")) && (!strcmp(args, ""))) // clear all history
		{
			printf("%s\n", "Cleared History!");
			char *path = malloc(1000 * sizeof(char));
			strcpy(path, initial_directory);
			strcat(path, "/history.txt");
			history_write = fopen(path, "w");
			fputs("", history_write);
			return 1;
		}
		if ((!strcmp(flag, "-d")) && (strcmp(args, "")))
		{
			int n = strlen(args);
			char *s = args;
			for (int i = 0; i < n; i++)
			{
				if (s[i] == '1' ||
				        s[i] == '2' ||
				        s[i] == '3' ||
				        s[i] == '4' ||
				        s[i] == '5' ||
				        s[i] == '6' ||
				        s[i] == '7' ||
				        s[i] == '8' ||
				        s[i] == '9' ||
				        s[i] == '0'
				   )
					continue;
				else
				{
					printf("%s\n", "Please enter a number as offset!!!");
					return 1;
				}
			}
			int x = atoi(args);
			delete_offset(x);
			return 1;
		}
		if ((!strcmp(flag, "")) && (!strcmp(args, "")))
		{
			// display all history
			print_history1();
			return 1;
		}
		printf("%s\n", "options supported: -c and -d");
		return -1;
	}
	if (!strcmp(command, "pwd")) //parent working directory
	{
		if (strcmp(args, ""))
		{
			printf("%s\n", "No arguments supported with this command!!!");
			return 1;
		}
		if (!strcmp(flag, "") || !strcmp(flag, "-P")) //-p is the default flag so no change
		{
			char pwd[100];
			getcwd(pwd, 100);
			printf("%s\n", pwd);
			return 1;
		}
		printf("%s\n", "options suppported: -P");
		return -1;
	}
	if (!strcmp(command, "echo")) //echo command   //done complete command
	{
		//handled the case for empty input
		if (!strcmp(args, ""))
		{
			printf("%s\n", "Invalid operand!!!");
			return 1;
		}
		if (!strcmp(flag, "-n")) //ignore the end line character
		{
			printf("%s", args);
			return 1;
		}
		if (!strcmp(flag, "-E")) //defualt implementaion
		{
			printf("%s\n", args);
			return 1;
		}
		if (!strcmp(flag, ""))
		{
			printf("%s\n", args);
			return 1;
		}
		printf("%s\n", "options suppported: -E and -n");
		return -1;
	}
	if (!strcmp(command, "cd")) //cd command
	{
		//handled the errors by errno library
		if (!strcmp(flag, "") || !strcmp(flag, "-P")) //-p is the defualt flag so no change
		{
			int res = chdir(args);
			if (res == 0)
				return 1;
			else
			{
				printf("Error: %s\n", strerror(errno));
				return 1;
			}
		}
		printf("%s\n", "options supported: -P");
		return -1;
	}
	return -1;
}
int handle_external_command(char *command, char *flag, char *args)
{
	if (!strcmp(command, "ls")) // ls command completed
	{
		//handled the case when some invalid flag is entered
		//provided feedback for all errors using errno.h header file
		if (!strcmp(flag, "") || !strcmp(flag, "-l") || !strcmp(flag, "-A"))
		{
			if (strcmp(args, ""))
			{
				printf("%s\n", "No arguments supported with this command!!");
				return -1;
			}
			printf("%s\n", initial_directory);
			char *path = malloc(1000 * sizeof(char));
			strcpy(path, initial_directory);
			strcat(path, "/ls");
			// printf("%s\n",path);
			pid_t ret_value = fork();
			int status;
			if (ret_value < 0)
			{
				printf("Child proces could not be created");
			}
			else if (ret_value == 0)
			{
				//child process
				execl(path, flag, NULL);
			}
			else
			{
				//parent process
				waitpid(ret_value, &status, 0);
				return 1;
			}
		}
		else
		{
			printf("%s\n", "options suppported: -l and -A");
			return -1;
		}
	}
	if (!strcmp(command, "mkdir"))
	{
		//handling the -p option properly without actually going into the deepest directory
		//to create the directory structure
		//handled invalid input (if any)
		//provided feedback of error (if any) using the errn.h header file
		//handled the case when some other flag apart from the ones provi
		if ((!strcmp(flag, "") || !strcmp(flag, "-p") || !strcmp(flag, "-v")) && (strcmp(args, "")))
		{
			char *path = malloc(1000 * sizeof(char));
			strcpy(path, initial_directory);
			strcat(path, "/mkdir");
			pid_t ret_value = fork();
			int status;
			if (ret_value < 0)
			{
				printf("Child proces could not be created");
			}
			else if (ret_value == 0)
			{
				//child process
				execl(path, flag, args, NULL);
			}
			else
			{
				//parent process
				waitpid(ret_value, &status, 0);
				return 1;
			}
		}
		else
		{
			printf("%s\n", "options suppported: -p and -v");
			return -1;
		}
	}
	if (!strcmp(command, "cat"))
	{
		//feature:
		//handling mutliple files concatentaion at a time
		//handled the case when user enters invalid file name
		//provided feedback for the error (if any) in displaying the content of a file
		if (!strcmp(flag, "") || !strcmp(flag, "-E") || !strcmp(flag, "-n"))
		{
			char *path = malloc(1000 * sizeof(char));
			strcpy(path, initial_directory);
			strcat(path, "/cat");
			pid_t ret_value = fork();
			int status;
			if (ret_value < 0)
			{
				printf("Child proces could not be created");
			}
			else if (ret_value == 0)
			{
				//child process
				execl(path, flag, args, NULL);
			}
			else
			{
				//parent process
				waitpid(ret_value, &status, 0);
				return 1;
			}
		}
		else
		{
			printf("%s\n", "options suppported: -E and -n");
			return -1;
		}
	}
	if (!strcmp(command, "date") && ((!strcmp(flag, "") || !strcmp(flag, "-R") || !strcmp(flag, "-u"))))
	{
		char *path = malloc(1000 * sizeof(char));
		strcpy(path, initial_directory);
		strcat(path, "/date");
		pid_t ret_value = fork();
		int status;
		if (ret_value < 0)
		{
			printf("Child proces could not be created");
		}
		else if (ret_value == 0)
		{
			//child process
			execl(path, flag, args, NULL);
		}
		else
		{
			//parent process
			waitpid(ret_value, &status, 0);
			return 1;
		}
		printf("%s\n", "options suppported: -R and -u");
		return -1;
	}
	if (!strcmp(command, "rm") && ((!strcmp(flag, "") || !strcmp(flag, "-i") || !strcmp(flag, "-v"))))
	{
		//defense against attacks:
		//preventing the deletion of the histroy file in which I am storing the history
		//preventing deletion of any code file as well
		//handled the case when given input is invalid
		//provided feedback for the error (if any) by using the errno.h header file
		char *path = malloc(1000 * sizeof(char));
		strcpy(path, initial_directory);
		strcat(path, "/rm");
		pid_t ret_value = fork();
		int status;
		if (ret_value < 0)
		{
			printf("Child proces could not be created");
		}
		else if (ret_value == 0)
		{
			//child process
			execl(path, flag, args, initial_directory, NULL);
		}
		else
		{
			//parent process
			waitpid(ret_value, &status, 0);
			return 1;
		}
		printf("%s\n", "options suppported: -i and -v");
		return -1;
	}
	printf("%s\n", "Unrecognized command!!!");
	return -1;
}
char* read_command_from(int* position, int n, char *command)
{
	char *string = malloc(1000 * sizeof(char));
	int counter = 0;
	string[0] = '\0';
	int actual_position = 0;
	while ((*position) < n)
	{
		if (counter == 0 && command[*position] == ' ')
			(*position)++;
		else if (command[*position] != ' ')
		{
			counter = 1;
			string[actual_position++] = command[(*position)++];
			string[actual_position] = '\0';
		}
		else if (command[*position] == ' ' && counter == 1)
			break;
	}
	return string;
}
int execute_command(char *command)
{
	// printf("%s",command);
	char *remaining_text = malloc(1000 * sizeof(char));
	int pos = 0;
	int *ptr = &pos;
	int n = strlen(command);
	char *actual_command = read_command_from(ptr, n, command);
	(*ptr)++;
	// printf("%d\n",(*ptr));
	char *flag = read_command_from(ptr, n, command);
	char *string = malloc(1000 * sizeof(char));
	int actual_position = 0;
	int counter = 0;
	if (strlen(flag) != 2 || flag[0] != '-')
	{
		string = flag;
		actual_position = strlen(flag);
		char *new_flag = malloc(1000 * sizeof(char));
		new_flag[0] = '\0';
		flag = new_flag;
		counter = 1;
	}
	while ((*ptr) < n)
	{
		if (counter == 0 && command[*ptr] == ' ')
			(*ptr)++;
		else if (command[position] != ' ')
		{
			counter = 1;
			string[actual_position++] = command[(*ptr)++];
			string[actual_position] = '\0';
		}
	}
	remaining_text = string;
	int status = handle_internal_command(actual_command, flag, remaining_text);
	if (status == -1) // not an internal command
		status = handle_external_command(actual_command, flag, remaining_text);
	return status;
}

int main()
{
	initial_size = 100;
	current_directory = malloc(100 * sizeof(char));
	initial_directory = malloc(1000 * sizeof(char));
	getcwd(initial_directory, 1000);
	char *input_line;
	int executed_correctly = 1;
	position = 0;
	while (1)
	{
		getcwd(current_directory, 100);
		printf("%s$ ", current_directory);
		input_line = take_input();
		// printf("%s\n",input_line);
		if (strcmp(input_line, "") == 0)
		{
			// printf("%s\n","Did not enter a command" );
			free(input_line);
			continue;
		}
		executed_correctly = execute_command(input_line);
		// printf("%d\n",executed_correctly );
		char *path = malloc(1000 * sizeof(char));
		strcpy(path, initial_directory);
		strcat(path, "/history.txt");
		history_write = fopen(path, "a");
		fputs(input_line, history_write);
		fputs("\n", history_write);
		fclose(history_write);
		if (executed_correctly == 10) // exit system call
			break;
		free(input_line);
	}
	return 0;
}