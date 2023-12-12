#include "main.h"

/**
  * str_chr - used to locate the first occurrence of a
  * specific character.
  * @s: the string to be scanned
  * @c: the charcter to be searched for in the string.
  * Return: NULL
  */

char *str_chr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return s;
		s++;
	}
	return (NULL);
}
