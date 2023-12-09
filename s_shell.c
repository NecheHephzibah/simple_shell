#include "main.h"

void handle_argument(char **arr, char **cmdline_args);
void execute_cmd(char **arr);

extern char **environ;

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
	char **env;

	while (1)
	{
		linePtr = source_input();
		arr = tok_input(linePtr, linePtr_copy, " \n", &tokCount);
		cmdline_args = get_cmdline_args(tokCount);
		handle_argument(arr, cmdline_args);

		if (strcmp(cmdline_args[0], "exit") == 0)
		{
			free_memory(arr, cmdline_args, linePtr_copy);
			exit(0);
		}
		if (strcmp(cmdline_args[0], "env") == 0)
		{
			for (env = environ; *env != NULL; env++)
				printf("%s\n", *env);
			free_memory(arr, cmdline_args, linePtr_copy);
			continue;
		}

		execute_cmd(cmdline_args);
		free_memory(arr, cmdline_args, linePtr_copy);
	}
	free(linePtr);
	return (0);
}


/**
 * handle_argument - function that copies command
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
	char *cmd = NULL, *address = getenv("PATH");
	char *addr_copy, *full_addr, *token_addr;
	pid_t pid;

	if (cmdline_args && address)
	{
		cmd = cmdline_args[0];
		addr_copy = strdup(address);
		token_addr = strtok(addr_copy, ":");
		while (token_addr != NULL)
		{
			full_addr = malloc(strlen(token_addr) + strlen(cmd) + 2);
			if (!full_addr)
			{
				perror("Memory allocation failed");
				free(addr_copy);
				return;
			}
			if (token_addr[strlen(token_addr) - 1] == '/')
				sprintf(full_addr, "%s%s", token_addr, cmd);
			else
				sprintf(full_addr, "%s/%s", token_addr, cmd);
			if (access(full_addr, X_OK) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					if (execve(full_addr, cmdline_args, NULL))
						perror("Execution failed, execve");
				}
				else if (pid < 0)
					perror("Execution failed: fork");
				else
					wait(NULL);
				free(full_addr);
				free(addr_copy);
				return;
			}
			free(full_addr);
			token_addr = strtok(NULL, ":");
		}
		free(addr_copy);
		printf("%s : Couldn't find command\n", cmd);
	}
}

