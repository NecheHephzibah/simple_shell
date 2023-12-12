#include "main.h"

/**
  * _strncmp - compares the first len charactrs of string 1
  * string 2, if they are equal or not.
  * @s1: string one.
  * @s2: string two.
  * @len: the length of the strings.
  * Return: 0;
  */

int _strncmp(char *s1, const char *s2, int len)
{
	int j;

	for (j = 0; j < len; j++)
	{
		if (s1[j] == '\0' || s2[j] == '\0')
			return (0);
		if (s1[j] != s2[j])
			return (s1[j] - s2[j]);
	}

	return (0);
}
