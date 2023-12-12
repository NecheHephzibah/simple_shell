#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char *_strncpy(char *dest, const char *src, int n);

/**
 * _getline - read a line from input stream
 * @lineptr: pointer to the array(string) of the line read
 * @n: pointer to the size in bytes of line read
 * @stream: pointer to the input stream
 *
 * Return: the number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char buf[1024];
	size_t bufflen = 1024;
	char *buff, *tempbuff;
	size_t i = 0, j = 0;
	ssize_t bytes_read;
	int fd;

	fflush(stdout);
	if (stream == stdin)
		fd = 0;

	if (*lineptr != NULL)
		free(*lineptr);

	buff = malloc(bufflen * sizeof(char));

	while (1)
	{
		if (i == bufflen) /*if buffer is full resize*/
		{
			tempbuff = malloc(2 * bufflen * sizeof(char));
			strncpy(tempbuff, buff, bufflen);
			free(buff);
			buff = tempbuff;
			tempbuff = NULL;
			bufflen = bufflen * 2;
		}

		bytes_read = read(fd, buf, 1024);
		if (bytes_read == 0)
		{
			if (i == 0 && j == 0)
				return (-1);
			buff[i + j] = '\0';
			break;
		}
		if (bytes_read > 0)
		{
			if (i == 0 && j == 0 && buf[j] == '\n')
			{
				buff[i + j] = '\0';
				*lineptr = malloc(sizeof(char));
				strncpy(*lineptr, buff, 1);
				*n = 1;
				free(buff);
				return (1);
			}
			for (j = 0; j < (size_t)bytes_read; j++)
			{
				if (buf[j] == '\n' || buf[j] == EOF)
				{
					buff[i + j] = '\0';
					break;
				}
				else if (buf[j] == '\b' && i > 0)
				{
					i = i - 1;
					continue;
				}
				else
				{
					buff[i + j] = buf[j];
				}
			}
			if ((buf[j] == '\n' || buf[j] == EOF) && (j < (size_t)bytes_read))
				break;
			i = i + j;
		}
	}
	*lineptr = malloc((i + j + 1) * sizeof(char));
	strncpy(*lineptr, buff, i + j + 1);
	*n = i + j + 1;
	free(buff);

	return (i + j);
}
