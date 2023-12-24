#include "main.h"

/*char ***split_cmd(char **arr);*/
void handle_argument(char **arr, char **cmdline_args);
void execute_cmd(char **cmdline_args, char **argv, char **environ);

/**
 * main - shell function.
 * @argc: argument count.
 * @argv: list of argument.
 * Return: (0) success.
 */

int main(int argc, char *argv[])
{
	char **linePtr = NULL;
	char *linePtr_copy = NULL;
	char **arr, **cmdline_args;
	int tokCount = 0, i = 0, len_linePtr = 0;
	char **env;
	unsigned long int exit_status = 0;

	(void)argc;
	while (1)
	{
		linePtr = source_input(&len_linePtr);
		i = 0;
		while (i < len_linePtr)
		{
		arr = tok_input(linePtr[i], linePtr_copy, " \n\t", &tokCount);

		if (arr[0] == NULL)
		{
			free(linePtr[i]);
			free(linePtr_copy);
			free(arr);
			break;
		}
		cmdline_args = get_cmdline_args(tokCount);
		handle_argument(arr, cmdline_args);

		if (_strcmp(cmdline_args[0], "exit") == 0)
		{
			if (cmdline_args[1])
				exit_status = str_to_num(cmdline_args[1]);
			free_memory(arr, cmdline_args, linePtr_copy);
			free(linePtr[i]);
			free(linePtr);
			if (exit_status != 0)
				exit(exit_status);
			else
				exit(0);
		}
		if (_strcmp(cmdline_args[0], "env") == 0)
		{
			for (env = environ; *env != NULL; env++)
				_printf("%s\n", *env);
			free_memory(arr, cmdline_args, linePtr_copy);
			free(linePtr[i]);
			break;
		}
		execute_cmd(cmdline_args, argv, environ);
		free_memory(arr, cmdline_args, linePtr_copy);
		free(linePtr[i]);
		i++;
		}
		free(linePtr);

		if (!(isatty(0)))
			exit(0);
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

	cmdline_args[arg_idx++] = _strdup(arr[0]);

	for (i = 1; arr[i] != NULL; i++)
	{
		cmdline_args[arg_idx++] = _strdup(arr[i]);
	}
	cmdline_args[arg_idx] = NULL;
}


/**
 * execute_cmd - function that executes user input in command line.
 * @cmdline_args: gets the array of comand line arguments.
 * @argv: initial command line arguments.
 * @environ: environment variable
 * Return: void.
 */

void execute_cmd(char **cmdline_args, char **argv, char **environ)
{
	char *cmd = NULL, *address = _getenv("PATH");
	char *addr_copy, *full_addr, *token_addr;
	pid_t pid;

	if (cmdline_args && address)
	{
		cmd = cmdline_args[0];
		addr_copy = _strdup(address);
		token_addr = strtok(addr_copy, ":");
		while ((token_addr != NULL) || (access(cmd, X_OK) == 0))
		{
			if (access(cmd, X_OK) == 0)
				full_addr = _strdup(cmd);
			else
				full_addr = _strconcat(token_addr, cmd);

			if (access(full_addr, X_OK) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					if (execve(full_addr, cmdline_args, environ))
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
		printf("%s: 1: %s: not found\n", argv[0], cmd);
	}
}

