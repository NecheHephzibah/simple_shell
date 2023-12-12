#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int indelim(char c, const char *delim);

/**
 * _strtok - split string into tokens (tokenize)
 * @str: the string
 * @delim: the delimiter strings
 *
 * Return: 0
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	static char *temp_str = NULL;
	static size_t i = 0;
	size_t j = 0, token_length = 0;

	if (str)
	{
		i = 0;
		if (temp_str)
			free(temp_str);
		temp_str = strdup(str);
		while (str[i] && indelim(str[i], delim))
			i++;
		while (str[i] && !(indelim(str[i], delim)))
		{
			token_length++;
			i++;
		}
		i = i - token_length;
		if (token_length > 0)
		{
			token = malloc((token_length + 1) * sizeof(char));
			while (str[i] && !(indelim(str[i], delim)))
			{
				token[j++] = str[i++];
				token[j] = '\0';
			}
			return (token);
		}
		free(temp_str);
		return (NULL);

	}
	if (temp_str && temp_str[i])
	{
		free(token);
		while (temp_str[i] && indelim(temp_str[i], delim))
			i++;
		while(temp_str[i] && !(indelim(temp_str[i], delim)))
		{
			token_length++;
			i++;
		}
		i = i - token_length;
		if (token_length > 0)
		{
			token = malloc((token_length + 1) * sizeof(char));
			while (temp_str[i] && !(indelim(temp_str[i], delim)))
			{
				token[j++] = temp_str[i++];
				token[j] = '\0';
			}
			return (token);
		}
		free(temp_str);
		return (NULL);
	}
	return (NULL);
}

/**
 * indelim - check if char is a delimiter
 * @c: the char
 * @delim: the delimiter string
 *
 * Return: 1 if char is in delim and 0 otherwise
 */
int indelim(char c, const char *delim)
{
	int i = 0;

	while (delim[i])
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}
