#include "main.h"

/**
 * free_memory - function that frees allocated memory.
 *
 * @arr: array that holds lists of arguments.
 * @cmdline_args: command line arguments.
 * @linePtr_copy: copy of the input string.
 *
 * Return: void.
 */
void free_memory(char **arr, char **cmdline_args, char *linePtr_copy)
{
	int w, m;

	for (w = 0; arr[w] != NULL; w++)
		free(arr[w]);
	free(arr);
	for (m = 0; cmdline_args[m] != NULL; m++)
		free(cmdline_args[m]);
	free(cmdline_args);
	free(linePtr_copy);
}
