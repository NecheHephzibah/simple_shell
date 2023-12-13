#include "main.h"

/**
 * tok_input - function that tokenizes the input.
 *
 * @linePtr: pointer to the input string.
 * @linePtr_copy: copy of the input string.
 * @delim: delimiter for strtok.
 *
 * Return: arr.
 */
char **tok_input(char *linePtr, char *linePtr_copy,
	const char *delim, int *tokCount)
{
	char *token;
	int i;
	char **arr;

	linePtr_copy = malloc(sizeof(char) * _strlen(linePtr));
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
	token = strtok(linePtr_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		arr[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	arr[i] = NULL;

	return (arr);
}
