#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
/**
 * _unsetenv - delete an environment variable
 * @name: the variable name
 *
 * Return: 0 if success
 */
int _unsetenv(const char *name)
{
	list_v *head = NULL;
	list_v *node, *temp, *prev;
	int i, index, environ_len = 0;
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
	/*Find the index of the node to delete*/
	index = 0;
	temp = head;
	while (temp)
	{
		if (strcmp(temp->name, name) == 0)
			break;
		temp = temp->next;
		index++;
	}

	/*Now to delete an environment variable "name"*/
	prev = (list_v *)&head;
	temp = head;
	i = 0;
	while (temp)
	{
		if (strcmp(temp->name, name) == 0) /*if variable present, delete the node*/
		{
			if (index = 0)
				head = temp->next;
			else
				prev->next = temp->next;
			free(temp);
			environ_len -= 1;
			break;
		}
		prev = temp;
		temp = temp->next;
		i++;
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
