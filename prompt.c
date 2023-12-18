#include "main.h"

/**
 * source_input - function that gets the input from the user.
 *
 * Return: linePtr.
 */
char **source_input(int *len)
{
	char *prompt = " $ ", *line = NULL;
	ssize_t storePrompt = 1;
	char **linePtr = NULL;
	size_t n = 0;
	int i = 0;

	if (isatty(0))
		_printf("%s", prompt);


	while (storePrompt > 0)
	{

		storePrompt = getline(&line, &n, stdin);

		if (storePrompt == -1 && isatty(0) && i == 0)
		{
			free(line);
			_printf("\n");
			exit(EXIT_FAILURE);
		}
		printf("%s\n", line);
		if (!(storePrompt == -1))
			free(line);
		i++;
	}
	printf("%d\n", i);
	
	linePtr = malloc(sizeof(char *) * i);
	storePrompt = 1;
	i = 0;
	if (lseek(0, 1, SEEK_SET) == -1)
		perror("lseek");
	exit(98);

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
	linePtr[i - 1] = NULL;
	*len = i - 1;
	printf("LinePtr[0] = %s\n", linePtr[0]);
	printf("LinePtr[1] = %s\n", linePtr[1]);
	printf("LinePtr[2] = %s\n", linePtr[2]);


	return (linePtr);
}
