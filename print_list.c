#include "main.h"

/**
 * print_list - print all the elements of a list_t list
 * @h: pointer to the list
 *
 * Return: the number of nodes in the list
 */
size_t print_list(const list_m *h)
{
	list_m *temp;
	int i = 0;

	temp = (list_m *)h;
	while (temp != NULL)
	{
		if (temp->line == NULL)
			printf("[0] (nil)\n");
		else
			printf("[%i] %s\n", temp->index, temp->line);
		i++;
		temp = temp->next;
	}
	return (i);
}
