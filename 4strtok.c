#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	char s[] = "/bin/ls -l -a";
	int i;
	const char delim[] = " ";
	char **p;
	p = malloc(10 * sizeof(char *));
	char *token;
	pid_t childpid;

	printf("String to split up: %s\n", s);

	token = strtok(s, delim);
	printf("Outside loop %s\n", token);
	i = 0;
	p[i++] = token;

	while (token != NULL)
	{
		token = strtok(NULL, delim);
		printf("Inside Loop%s\n", token);
		p[i++] = token;
	}
	p[i] = NULL;

	i = 0;
	while (p[i] != NULL)
	{
		printf("yeh %s\n", p[i++]);
	}
	
	childpid = fork();

	if (childpid == 0)
		execve(p[0], p, NULL);
	else
	{
		wait(NULL);
		printf("I waited.\n");
	}
	return (0);
}
