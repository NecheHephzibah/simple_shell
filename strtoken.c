#include "main.h"

/**
 * tok_input - function that tokenizes the input.
 *
 * @linePtr: pointer to the input string.
 * @linePtr_copy: copy of the input string.
 * @delim: delimiter for strtok.
 * @tokCount: counts the number of token
 * Return: arr.
 */
char **tok_input(char *linePtr, char *linePtr_copy,
	const char *delim, int *tokCount)
{
	char *token;
	int i;
	char **arr;

	linePtr_copy = malloc(sizeof(char) * _strlen(linePtr) + 1);
	if (linePtr_copy == NULL)
	{
		perror("Error... memory allocation");
		exit(EXIT_FAILURE);
	}
	_strcpy(linePtr_copy, linePtr);
	token = strtok(linePtr, delim);
	while (token != NULL)
	{
		(*tokCount)++;
		token = strtok(NULL, delim);
	}
	(*tokCount)++;
	arr = malloc(sizeof(char *) * (*tokCount));
	if (arr == NULL)
	{
		perror("Error... memory allocation");
		exit(EXIT_FAILURE);
	}
	token = strtok(linePtr_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		arr[i] = _strdup(token);
		if (arr[i] == NULL)
		{
			perror("Error... memory allocation");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, delim);
	}
	arr[i] = NULL;
	free(linePtr_copy);
	return (arr);
}
