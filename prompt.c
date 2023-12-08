#include "main.h"

/**
 * source_input - function that gets the input from the user.
 *
 * Return: linePtr.
 */
char *source_input(void)
{
	char *prompt = "(Xshell)$ ";
	ssize_t storePrompt;
	char *linePtr = NULL;
	size_t n = 0;

	printf("%s", prompt);
	storePrompt = getline(&linePtr, &n, stdin);

	if (storePrompt == -1)
	{
		printf("Exiting shell...\n");
 		exit(EXIT_FAILURE);
	}

	return (linePtr);
}