#include "main.h"

/**
 * get_cmdline_args - function that creates cmdline_args.
 * @tokCount: number of tokens.
 *
 * Return: cmdline_args.
 */
char **get_cmdline_args(int tokCount)
{
	char **cmdline_args;

	cmdline_args = malloc(sizeof(char *) * (tokCount));

	if (cmdline_args == NULL)
	{
		perror("Error: cmdline_args memory allocation");
		exit(EXIT_FAILURE);
	}

	return (cmdline_args);
}
