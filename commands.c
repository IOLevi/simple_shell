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
	//ls -a

	while (s[i] == ' ' && s[i] != '\0')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);

	while (s[i] != '\0')
	{
		tokencounter++;
		while(s[i] != ' ' && s[i] != '\0')
			i++;

		while(s[i] == ' ' && s[i] !='\0')
			i++;


	}
	return (tokencounter);
}
/**
 * _strok - funtion that tokenizes a string (resembles strtok
 *@s: string to tokenize
 *@delim: deliminator for string
 *
 *Return: token. Otherwise 0.
 */
char * _strtok(char *s, char *delim)
{
	static int spoint = 0;
	unsigned int i = 0, x = 0;
	static int length = 0;
	static char *copy;


	if (s != NULL)
	{
		length = _strlen(s);
		while(s[i] != '\0')
		{
			for(x = 0; delim[x] != '\0'; x++)
			{
				if (s[i] == delim[x])
					s[i] = '\0';
			}
			i++;
		}
		i = 0;
		while(s[i] == '\0' && i < length)
			i++;

		spoint = i;
		
		if (s[i] != '\0')
		{
			copy = s;
			return (s + i);
		}
		return (NULL);
	}

	if (s == NULL)
	{
		i = spoint;
		s = copy; 
		while(s[i] != '\0' && i < length)
			i++;
		while(s[i] == '\0' && i < length)
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
	int i = 0, j = 0;
	PDIRECT *head, *temp, *temp2;

	head = malloc(sizeof(PDIRECT));
	if (!head)
		//TODO: if malloc fails want to exit program
		return (NULL);
	head->next = NULL;

	path = _getenv("PATH");

	token = _strtok(path, delim);
	head->s = token;

	temp = head;
	while (token != NULL)
	{
		token = _strtok(NULL, delim);
		if (token != NULL)
		{
			temp2 = malloc(sizeof(PDIRECT));
			//TODO: if malloc fails want to undo the entire list and exit program
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
	struct stat st; /** struct part of the library to look at stat */
	char *buf;
	int commandinputlen = 0, dirlen = 0, i, j;

	commandinputlen= _strlen(commandinput);
	while(head != NULL)
	{
		dirlen = _strlen(head->s); /** finds the length of each s in the path */

		buf = malloc(sizeof(char) * (commandinputlen + dirlen) + 2);
		if (!buf)
			return (NULL);

		for (i = 0; i < dirlen; i++)
		{
			buf[i] = (head->s)[i]; /** goes through each string in the list and sets to buf */
		}
		buf[i++] = '/';
		for (j = 0; j < commandinputlen; j++)
		{
			buf[j + i] = commandinput[j];
		}
		buf[j + i] = '\0';

		if (stat(buf, &st) == 0)
		{
			return (buf);

		}

		free(buf);
		head = head->next;
	}

	return (NULL);
}
/**
 * errmessage - prints error message when command not found
 * @c: user command
 * @p: pointer to name of the program
 * @i: counter, indicating number of user commands during life of program
 */
void errmessage(char **c, char *p, int i)
{
	char *t;

	t = malloc(sizeof(char) * i);
	_itoa(i, t);
	write(STDOUT_FILENO, p, _strlen(p));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, t, _strlen(t));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, c[0], _strlen(c[0]));
	write(STDOUT_FILENO, ": not found\n", 12);

	free(t);
}

void CDerrmessage(char **c, char *p, int i)
{
	char *t;

	t = malloc(sizeof(char) * i);
	_itoa(i, t);
	write(STDOUT_FILENO, p, _strlen(p));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, t, _strlen(t));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, c[0], _strlen(c[0]));
	write(STDOUT_FILENO, ": can't cd to ", 14);
	write(STDOUT_FILENO, c[1], _strlen(c[1]));
	write(STDOUT_FILENO, "\n", 1);
	free(t);
}
