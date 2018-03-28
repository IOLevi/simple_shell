#include "holberton.h"

/**
 * checkexit - implements exit builtin and exits with supplied error #
 * @p: user command strings
 * Return: If user entered exit, returns entered errnum, or 97 by default; otherwise 0
 */
int checkexit(char **token)
{
	char check[] = "exit";
	int errnumber = 0;

	if (_strcmp(token[0], check) == 0) /** means that the token at position 0 is exit*/
	{
		if (token[1])
		{
			errnumber = _atoi(token[1]);
		}
		//_atoi returns -1 if the conversion of ascii to int failed
		//this would return 97 as default
		if (errnumber == -1)
			//TODO: matchup behavior to SH. THis would print an error message invalid exit status
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
 * @findcommand: malloced string path/to/file from PATH function
 */
void __exit(int errnum, char **p, char *getline, PDIRECT *head, char *findcommand)
{
	unsigned int i = 0;
	PDIRECT *tmp;

	if (p)
		free(p);
	if (getline)
		free(getline);
	//free linked list
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	if (findcommand)
		free(findcommand);
	exit(errnum);
}