
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]);

int _printf(const char *format, ...);

int _strcmp(char *s1, char *s2);

char *_strdup(char *str);

char *_strconcat(char *s1, char *s2);

int _strlen(char *s);

char *_strcpy(char *dest, char *src);

void handle_argument(char **arr, char **cmdline_args);

void execute_cmd(char **cmdline_args, char **argv, char **environ);

void free_memory(char **arr, char **cmdline_args, char *linePtr_copy);

char **get_cmdline_args(int tokCount);

char *source_input(void);

char **tok_input(char *linePtr, char *linePtr_copy,
	const char *delim, int *tokCount);


#endif
