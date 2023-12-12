#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
const extern char **environ;
char *str_concat(char *name, char *value);
/**
 * _setenv - change or add an environment variable
 * @name: the variable name
 * @value: the value of the variable
 * @overwrite: 0 if variable should not be overwritten when it already exist
 *
 * Return: 0 if success
 */
int _setenv(const char *name, const char *value, int overwrite)
 {
	list_v *head = NULL;
	list_v *node, *temp;
	int i, environ_len = 0;
	char **environ_copy;
	
	while (environ[environ_len])   /*Compute the length of the environ var*/
		environ_len++;

	/*Create a copy of the environ variable in a linked list*/
	for (i = 0; i < environ_len; i++)
	{
		node = malloc(sizeof(list_v));
		if (head == NULL)
		{
			head = node;
			node->name = strtok(environ[i], "=");
			node->value = strtok(NULL, "=");
			node->next = NULL;
		}
		else
		{
			temp = head;
			while (temp && temp->next)
				temp = temp->next;
			temp->next = node;
			node->name = strtok(environ[i], "=");
			node->value = strtok(NULL, "=");
			node->next = NULL;
		}
	}

	temp = head;
	while (temp)
	{
		if (strcmp(temp->name, name) == 0 && overwrite != 0) /*variable present and overwrite set*/
		{
			temp->value = value;
				break;
		}
		else if (strcmp(temp->name, name) == 0 && overwrite == 0) /*variable present and no overwrite*/
		{
			break;
		}
		if (temp->next == NULL)  /*variable not present, add new node for variable*/
		{
			node = malloc(sizeof(list_v));
			temp->next = node;
			node->name = name;
			node->value = value;
			node->next = NULL;
			environ_len++;
			break;
		}

		temp = temp->next;
	}

	environ_copy = malloc(sizeof(&(environ[0])) * (environ_len + 1));
	temp = head;
	i = 0;
	while (temp)
	{
		environ_copy[i] = str_concat(temp->name, temp->value);
		temp = temp->next;
		i++;
	}
	environ_copy[i] = NULL;
	environ = environ_copy;

	return (0);
 }
/**
 * str_concat - concatenate variable name and value
 * @name: the varibale name
 * @value: the value of the variable
 *
 * Return: the concatenated string
 */
char *str_concat(char *name, char *value)
{
	char *new_str;
	size_t len, i, j;

	len = strlen(name) + strlen(value) + 2;
	new_str = malloc(len * sizeof(char));
	if (new_str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < strlen(name); i++)
		new_str[i] = name[i];
	new_str[i] = '=';
	for (i = strlen(name) + 1, j = 0; j < strlen(value); i++, j++)
		new_str[i] = value[j];
	new_str[i] = '\0';

	return(new_str);
}
