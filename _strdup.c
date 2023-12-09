#include <stdlib.h>
/**
 * _strdup - function to duplicate str and return pointer to newstr
 * @str: the string
 * Return: pointer to new str
 */
char *_strdup(char *str)
{
	int i = 0, j;
	char *tmp = str;
	char *newstr;

	if (str == 0)
		return (0);
	while (*str++)
		++i;
	newstr = malloc((i + 1) * sizeof(char));
	if (newstr == 0)
		return (0);
	for (j = 0; j < (i + 1); j++)
		newstr[j] = tmp[j];
	return (newstr);
}
