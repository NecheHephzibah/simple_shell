#include "main.h"

void execute_cmd(char **arr);

/**
 * main - shell function.
 *
 * Return: (0) success.
 */

int main(void)
{
	char *prompt = "(Xshell)$ ";
	ssize_t storePrompt;
	char *linePtr = NULL, *linePtr_copy = NULL, *token;
	size_t n = 0;
	const char *delim = " \n";
	int i, tokCount = 0;
	char **arr;
	while (1)
	{
		printf("%s", prompt);
		storePrompt = getline(&linePtr, &n, stdin);

		if (storePrompt == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		linePtr_copy = malloc(sizeof(char) * storePrompt);
		if (linePtr_copy == NULL)
		{
			perror("Error... memory allocation");
			return (-1);
		}

		strcpy(linePtr_copy, linePtr);

		token = strtok(linePtr, delim);
		while (token != NULL)
		{
			tokCount++;
			token = strtok(NULL, delim);
		}
		tokCount++;

		arr = malloc(sizeof(char *) * tokCount);
		token = strtok(linePtr_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			arr[i] = malloc(sizeof(char) * strlen(token) + 1);
			arr[i] = strdup(token);
			token = strtok(NULL, delim);
		}
		arr[i] = NULL;
		execute_cmd(arr);
		free(linePtr_copy);
	}
	free(linePtr);
}

/**
 * execute_cmd - function that executes user input in command line.
 * @arr: gets the array of token.
 * Return: void.
 */

void execute_cmd(char **arr)
{
	char *command = NULL;
	pid_t pid = fork();

	if (arr)
	{
		command = arr[0];

		if (pid == 0)
		{
			if (execve(command, arr, NULL))
				perror("Error: execve");
		}
		else if (pid < 0)
			perror("Error: fork");
		else
			wait(NULL);
	}
}

