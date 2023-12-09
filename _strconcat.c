#include <stdlib.h>
/**
 * _strconcat - concatenate two strings to get fullpath
 * @s1: first string
 * @s2: second string
 * Return: pointer to new string
 */
char *_strconcat(char *s1, char *s2)
{
	int i = 0, j = 0, k;
	char *tmp_s1;
	char *tmp_s2;
	char *newstr;
	char *tmp_newstr;

	if (s1 == 0)
		s1 = "";
	if (s2 == 0)
		s2 = "";
	tmp_s1 = s1;
	tmp_s2 = s2;
	while (*s1++)
		i++;
	while (*s2++)
		j++;
	k = i + j;
	newstr = malloc((k + 2) * sizeof(char));
	if (newstr == 0)
		return (0);
	tmp_newstr = newstr;
	while (*tmp_s1)
		*newstr++ = *tmp_s1++;
	*newstr++ = '/';
	while (*tmp_s2)
		*newstr++ = *tmp_s2++;
	*newstr = '\0';
	return (tmp_newstr);
}
