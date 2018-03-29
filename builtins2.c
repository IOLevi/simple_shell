#include "holberton.h"

/**
 * checkexit - implements exit builtin and exits with supplied error #
 * @token: user command strings
 * Return: If user entered exit, returns entered errnum
 */
int checkexit(char **token)
{
	char check[] = "exit";
	int errnumber = 0;

	if (_strcmp(token[0], check) == 0)
	{
		if (token[1])
		{
			errnumber = _atoi(token[1]);
		}
		if (errnumber == -1)
			return (2);
		else
			return (errnumber);
	}
	return (-1);
}

/**
 * __exit - gracefully exits by freeing all malloced memory
 * @errnum: exits with this error number
 * @p: heap array of char pointers used to store comands
 * @getline: pointer to malloc space from getline function call
 * @head: head of linked list
 * @fc: malloced string path/to/file from PATH function
 * @predirect: malloc string of previous directory
 */
void __exit(int errnum, char **p, char *getline, PDIRECT *head, char *fc, char *predirect)
{
	PDIRECT *tmp;

	if (p)
		free(p);
	if (getline)
		free(getline);
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	if (fc)
		free(fc);
	if (predirect)
		free(predirect);
	exit(errnum);
}
