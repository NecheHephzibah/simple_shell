#include "main.h"
list_m *add_node(list_m **head, char *line, int index);
char *get_node(list_m *head, int index);
void free_list(list_m *head);
/**
 * source_input - function that gets the input from the user.
 * @len: the length of the input.
 * Return: linePtr.
 */
char **source_input(int *len)
{
	char *prompt = " $ ", *line = NULL;
	ssize_t storePrompt = 1;
	char **linePtr = NULL;
	size_t n = 0;
	int i = 0;
	list_m *head;

	head = NULL;

	if (isatty(0))
		_printf("%s", prompt);


	while (storePrompt > 0)
	{
		line = NULL;
		n = 0;
		storePrompt = getline(&line, &n, stdin);

		if (storePrompt == -1 && isatty(0) && i == 0)
		{
			free(line);
			_printf("\n");
			exit(EXIT_FAILURE);
		}

		if (storePrompt != -1 && strtok(line, " \n\t") == NULL && !(isatty(0)))
		{
			free(line);
			continue;
		}	

		if (!(storePrompt == -1))
		{
			add_node(&head, line, i);
			free(line);
		}
		i++;
		if (isatty(0))
		{
			i++;
			break;
		}
		if (storePrompt == -1)
			free(line);
	}

	*len = i - 1;
	linePtr = malloc(sizeof(char *) * i);
	i = 0;

	while (i < *len)
	{
		linePtr[i] = get_node(head, i);
		i++;
	}
	linePtr[i] = NULL;
	free_list(head);

	return (linePtr);
}

/**
 * add_node - add a new node at the end of a linked list
 * @head: pointer to the list
 * @line: pointer to the node element
 * @index: the node index
 *
 * Return: pointer to new node
 */
list_m *add_node(list_m **head, char *line, int index)
{
	list_m *new;
	list_m *temp;

	temp = *head;
	new = malloc(sizeof(list_m));
	if (new == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->line = _strdup(line);
	new->index = index;
	if (temp == NULL)
	{
		new->next = NULL;
		*head = new;
		return (new);
	}
	while (temp != NULL && temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;

	return (new);
}

/**
 * get_node - find the nth node of a list_m list
 * @head: pointer to the head node
 * @index: index of the node starting at 0
 *
 * Return: line at the nth node or NULL if node does not exist
 */
char *get_node(list_m *head, int index)
{
	list_m *temp;
	int i = 0;

	temp = head;
	while (temp)
	{
		if (i == index)
			return (temp->line);
		temp = temp->next;
		i++;
	}

	return (NULL);
}
/**
 * free_list - free a list_m list
 * @head: pointer to the list
 *
 * Return: void
 */
void free_list(list_m *head)
{
	list_m *temp;

	temp = head;
	if (temp == NULL)
		return;
	while (temp != NULL)
	{
		head = temp->next;
		free(temp);
		temp = head;
	}
}
