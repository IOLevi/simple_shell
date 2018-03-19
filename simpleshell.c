#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
/**
 * struct direc - struct to hold linked list of PATH values
 * @s: directory path
 * @next: pointer to next node
 */
typedef struct direc
{
	char *s;
	struct direc *next;

} PDIRECT;

/**
 * *_getenv - returns an environmental variable value
 * @name: key to access the env value
 * Return: pointer to the value
 */
char *_getenv(const char *name)
{
	extern char **environ;
	char *finder = NULL;
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
 * linkedpath - builds a linked list of the PATH
 * Return: pointer to head of the linked list
 */
PDIRECT *linkedpath(void)
{
	char *path, *token = NULL, *delim = ":";
	int i = 0, j = 0;
	PDIRECT *head, *temp, *temp2;

	head = malloc(sizeof(PDIRECT));
	head->next = NULL;

	path = _getenv("PATH");

	token = strtok(path, delim);
	head->s = token;

	temp = head;
	while (token != NULL)
	{
		token = strtok(NULL, delim);
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
 * _strlen - finds the length of a string
 * @s: pointer to the string
 * Return: the length of the string, or zero if empty
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}

	return (i);
}

/**
 * findcommand - uses stat to find a file in the path
 * @head: head pointer to the linked list of path directories
 * @f: user entered command to check in the path
 * Return: pointer to full path to a command if it exists; otherwise null;
 */
char *findcommand(PDIRECT *head, char *f)
{
	struct stat st;
	char *buf;
	int flen = 0, dirlen = 0, i, j;

	/* works 1:11pm evanday
	while (head)
	{
		printf("%s\n", head->s);
		head = head->next;
	} */

	//printf("%s\n", f); also works
	flen = _strlen(f);
	//printf("%d\n", flen); also works
	while(head)
	{
		dirlen = _strlen(head->s);

		buf = malloc(sizeof(char) * (flen + dirlen) + 2);
		if (!buf)
			return (NULL);

		//building a string with the /path/to/cmd
		for (i = 0; i < dirlen; i++)
		{
			buf[i] = (head->s)[i];
		}
		buf[i++] = '/';
		for (j = 0; j < flen; j++)
		{
			buf[j + i] = f[j];
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
 * _strcmp - compares two strings
 * @s1: first operand
 * @s2: second operand
 *
 * Return: positive if s1 is bigger, 0 if they are the same, otherwise negative
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);

}

/**
 * _atoi - converts string to integer
 * @s: string to convert
 * Return: -1 if it fails
 */
int _atoi(char *s)
{
	int sum = 0;

	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			sum *= 10;
			sum = sum + (*s - '0');
			s++;
		}
		else
		{
			return (-1);
		}
	}

	return (sum);
}

/**
 * checkexit - implements exit builtin and exits with supplied error #
 * @p: user command strings
 */
void checkexit(char **p)
{
	char check[] = "exit";
	int errnumber = 0;

	if (_strcmp(p[0], check) == 0)
	{
		printf("I am here\n");
		//if there is a second argument
		if (p[1])
		{
			errnumber = _atoi(p[1]);
			printf("%d\n", errnumber);
		}

		//TODO: add code for freeing everything? or rewrite to return error
		// number and do the freeing in main
		errnumber > -1 ? exit(errnumber) : exit(0);
	}
}

/**
 * idea to use a function to check for builtins...not sure
 */
/*
void checkforbuiltins(char **p)
{
	//loop through
	int i = 0; 
	char *builtins[] = {"exit", "env"};


	if (_strcmp(*p, builtins[i]))
} */

/**
 * checkenv - implements the env builtin command
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

/**
 * main - custom very lightweight shell
 * Return: 0
 */
int main()
{
	char *b = NULL, *token, *delim = " \n", **p, prompt[] = "($) ";
	char *cmdinpath;
	int readnum, i = 0;
	size_t len = 0;
	pid_t childpid;
	PDIRECT *head;

	p = malloc(10 * sizeof(char *));
	head = linkedpath();
	while (1)
	{
		write(STDOUT_FILENO, prompt, 4);
		i = 0;
		readnum = getline(&b, &len, stdin);
		
		//printf("Chars read from line: %d, length: %zu\n", readnum, len);

		token = strtok(b, delim);

		p[i++] = token;

		while (token != NULL)
		{
			token = strtok(NULL, delim);
			p[i++] = token;
		}

		i = 0;
		/*
		while (p[i] != NULL)
		{
			printf(":%s:\n", p[i++]);
		}*/

		childpid = fork();
		if (childpid == 0)
		{
			//checkforbuiltins()
			checkexit(p);
			if (checkenv(p))
				continue;
			execve(p[0], p, NULL);
			cmdinpath = findcommand(head, p[0]);
			
			//not sure if this works and might lose memory this way cuz of malloc
			//TODO: copy to a buffer and then free the heap variable;
			execve(cmdinpath, p, NULL);
			//any code that runs here is the error message because exec didnt call
		}
		else
		{
			wait(NULL);
			checkexit(p);
		}
	}
	return (0);
}
