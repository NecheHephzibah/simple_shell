#include "main.h"

/**
  * _getenv - function that gets the environment variable of a PATH.
  * @name: the name of the path.
  * Return: NULL.
  */

char *_getenv(const char *name)
{
	char **env;
	char *find_sign;
	int len_name;

	for (env = environ; *env != NULL; env++)
	{
		find_sign = str_chr(*env, '=');

		if (find_sign == NULL)
			continue;

		len_name = find_sign - *env;
		if (_strncmp(*env, name, len_name) == 0 && name[len_name] == '\0')
			return (find_sign + 1);
	}
	return (NULL);
}
