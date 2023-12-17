#include "main.h"

/**
 * source_input - function that gets the input from the user.
 *
 * Return: linePtr.
 */
char **source_input(void)
{
	char *prompt = " $ ";
	ssize_t storePrompt = 1;
	char **linePtr = NULL;
	size_t n = 0;
	int i = 0;

	if (isatty(0))
		_printf("%s", prompt);

	linePtr = malloc(sizeof(char *) * 3);
	while (storePrompt > 0)
	{
		storePrompt = getline(&linePtr[i], &n, stdin);

		if (storePrompt == -1 && isatty(0) && i == 0)
		{
			free(linePtr[i]);
			free(linePtr);

			_printf("\n");
			exit(EXIT_FAILURE);
		}

		i++;

	}

	printf("LinePtr[0] = %s\n", linePtr[0]);
	printf("LinePtr[1] = %s\n", linePtr[1]);
	printf("LinePtr[2] = %s\n", linePtr[2]);

	return (linePtr);
}
