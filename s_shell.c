#include "main.h"

void handle_argument(char **arr, char **cmdline_args);
void execute_cmd(char **arr);


/**
 * main - shell function.
 *
 * Return: (0) success.
 */

int main(void)
{
	char *linePtr = NULL, *linePtr_copy = NULL;
	char **arr, **cmdline_args;
	int tokCount = 0;

	while (1)
	{
		linePtr = source_input();
		arr = tok_input(linePtr, linePtr_copy, " \n", &tokCount);
		cmdline_args = get_cmdline_args(tokCount);
		handle_argument(arr, cmdline_args);
		execute_cmd(cmdline_args);
		free_memory(arr, cmdline_args, linePtr_copy);
	}
	free(linePtr);
	return (0);
}


 /* handle_argument - function that copies command
 * and its arguments separately.
 * @arr: array that hold lists of arguments.
 * @cmdline_args: command line arguments that would be
 * passed by users.
 * Return: void.
 */

void handle_argument(char **arr, char **cmdline_args)
{
	int arg_idx = 0;
	int i;

	cmdline_args[arg_idx++] = strdup(arr[0]);

	for (i = 1; arr[i] != NULL; i++)
	{
		cmdline_args[arg_idx++] = strdup(arr[i]);
	}
	cmdline_args[arg_idx] = NULL;
}


/**
 * execute_cmd - function that executes user input in command line.
 * @cmdline_args: gets the array of comand line arguments.
 * Return: void.
 */

void execute_cmd(char **cmdline_args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(cmdline_args[0], cmdline_args, NULL) == -1)
		{
			perror("Error: execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error: fork");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

