#include "holberton.h"
/**
 * tokencount - returns the number of tokens from the user input
 * @s: the string returned by getline
 * Return: the number of tokens, or zero if no input
 */
int tokencount(char *s)
{
	int tokencounter = 0;
	int i = 0;

	while (s[i] == ' ' && s[i] != '\0')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);

	while (s[i] != '\0')
	{
		tokencounter++;
		while (s[i] != ' ' && s[i] != '\0')/** goes through all characters */
			i++;

		while (s[i] == ' ' && s[i] != '\0') /** goes through all spaces */
			i++;


	}
	return (tokencounter);
}
/**
 * _strtok - funtion that tokenizes a string
 * @s: string to tokenize
 * @delim: deliminator for string
 * Return: token. Otherwise 0.
 */
char *_strtok(char *s, char *delim)
{
	static int spoint;
	int i = 0, x = 0;
	static int length;
	static char *copy;

	if (s != NULL)
	{
		length = _strlen(s);
		while (s[i] != '\0') /** replaces delim with null byte*/
		{
			for (x = 0; delim[x] != '\0'; x++)
			{
				if (s[i] == delim[x])
					s[i] = '\0';
			}
			i++;
		}
		i = 0;
		while (s[i] == '\0' && i < length) /** removes leading null bytes*/
			i++;

		spoint = i; /**spoint is now start of string */

		if (s[i] != '\0')
		{
			copy = s; /** makes string static */
			return (s + i); /** return start of string */
		}
		return (NULL);
	}
	else
	{
		i = spoint;
		s = copy;
		while (s[i] != '\0' && i < length) /**goes through characters */
			i++;
		while (s[i] == '\0' && i < length) /**goes through null bytes */
			i++;
		spoint = i;
		if (s[i] != '\0')
			return (s + i);
		return (NULL);
	}
}

/**
 * linkedpath - builds a linked list of the PATH
 * Return: pointer to head of the linked list
 */
PDIRECT *linkedpath(void)
{
	char *path, *token = NULL, *delim = ":";
	PDIRECT *head, *temp, *temp2;

	head = malloc(sizeof(PDIRECT));
	if (!head)
		return (NULL);
	head->next = NULL;

	path = _strdup(_getenv("PATH"));

	token = _strtok(path, delim);
	head->s = token;

	temp = head;
	while (token != NULL)
	{
		token = _strtok(NULL, delim);
		if (token != NULL)
		{
			temp2 = malloc(sizeof(PDIRECT));
			temp2->s = token;
			temp2->next = NULL;
			temp->next = temp2;
			temp = temp2;
		}
	}
	return (head);
}

/**
 * findcommand - uses stat to find a file in the path
 * @head: head pointer to the linked list of path directories
 * @commandinput: user entered command to check in the path
 * Return: pointer to full path to a command if it exists; otherwise null;
 */
char *findcommand(PDIRECT *head, char *commandinput)
{

	char *buf;
	int commandinputlen = 0, dirlen = 0, i, j;


	commandinputlen = _strlen(commandinput);
	while (head != NULL)
	{
		dirlen = _strlen(head->s);

		buf = malloc(sizeof(char) * (commandinputlen + dirlen) + 2);
		if (!buf)
			return (NULL);

		for (i = 0; i < dirlen; i++)
		{
			buf[i] = (head->s)[i];
		}
		buf[i++] = '/';
		for (j = 0; j < commandinputlen; j++)
		{
			buf[j + i] = commandinput[j];
		}
		buf[j + i] = '\0';

		if (access(buf, X_OK) == 0)
		{
			return (buf);

		}

		free(buf);
		head = head->next;
	}

	return (NULL);
}
