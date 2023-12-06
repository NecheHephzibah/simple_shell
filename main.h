
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void);

void handle_argument(char **arr, char **cmdline_args);

void execute_cmd(char **arr);

void free_memory(char **arr, char **cmdline_args, char *linePtr_copy);

char **get_cmdline_args(int tokCount);

char *source_input(void);

char **tok_input(char *linePtr, char *linePtr_copy,
	const char *delim, int *tokCount);


#endif
