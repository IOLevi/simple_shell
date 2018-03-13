#include "holberton.h"

/**
 * changedir - changes working directory to user entered path
 * @p: pointer to user entered commands
 * Return: 1 if successful
 */
int changedir(char **p, CHDIRECT *predirect)
{
	char cd[] = "cd";
	char tilde[] = "~";
	char dash[] = "-";
	char *s;

	if (_strcmp(p[0], cd) == 0)
	{

		predirect->boo = 1;
		if (_strcmp(p[1], tilde) == 0)
		{
			s = getenv("HOME");
			predirect->s = _strdup(getenv("PWD"));
			chdir(s);


		}
		else if(_strcmp(p[1], dash) == 0)
		{


			chdir(predirect->s);
			write(STDOUT_FILENO, predirect->s, _strlen(predirect->s));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			predirect->s = _strdup(getenv("PWD"));
			if (chdir(p[1]) == -1)
				return (-1);
		}


	}

	return (0);
}

/**
 * *_getenv - returns an environmental variable value
 * @name: key to access the env value
 * Return: pointer to the value
 */
char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0, j, len = 0;

	if (!name)
		return (NULL);
	else
	{
		while (name[len] != '\0')
			len++;
	}

	while (environ[i])
	{

		//TODO: I think should add '=' as terminating condition
		for (j = 0; j < len && *(environ[i] + j) != '\0'; j++)
		{
			if (name[j] != *(environ[i] + j))
				break;

			if (j == len - 1)
				return (environ[i] + j + 2);
		}

		i++;
	}

	return (NULL);
}
/**
 * checkenv - checks to see if the token is the env
 * @p: user supplies command line arguments
 * Return: returns 1 if user entered the command; zero otherwise
 */
int checkenv(char **p)
{
	extern char **environ;
	char command[] = "env";
	int i = 0;

	if (_strcmp(*p, command) == 0)
	{
/** environ is an array of all the values that represent the shell environment*/
/** this loop prints each environmental variable*/
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (0);
}
