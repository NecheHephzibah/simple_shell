
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]);

extern char **environ;

int _printf(const char *format, ...);

unsigned long int str_to_num(char *s);

int _strcmp(char *s1, char *s2);

int _strncmp(char *s1, const char *s2, int len);

char *str_chr(char *s, char c);

char *_getenv(const char *name);

char *_strdup(char *str);

char *_strconcat(char *s1, char *s2);

int _strlen(char *s);

char *_strcpy(char *dest, char *src);

void handle_argument(char **arr, char **cmdline_args);

void execute_cmd(char **cmdline_args, char **argv, char **environ);

void free_memory(char **arr, char **cmdline_args, char *linePtr_copy);

char **get_cmdline_args(int tokCount);

char **source_input(int *len);

char **tok_input(char *linePtr, char *linePtr_copy,
		const char *delim, int *tokCount);

/**
 * struct list_l - linked list of command line args
 * @line: a line of command
 * @next: the next node command line
 */
typedef struct list_l
{
	char *line;
	int index;
	struct list_l *next;
} list_m;

#endif
