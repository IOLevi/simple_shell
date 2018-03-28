#include "holberton.h"
/**
 * main - custom very lightweight shell
 * @argc: number of command line arguments
 * @argv: pointer to command line arguments
 * Return: 0
 */
int main(int argc __attribute__ ((unused)), char **argv)
{
	char *strinput = NULL, *token = NULL, **storetoken = NULL, prompt[] = "($) ";
	char *cmdinpath = NULL, *delim = "\n "; /**changed order of delim for betty */
	int readnum, i = 0, errnum = 0, size = 0, counter = 0, CDvalue = 0;
	size_t len = 0;
	pid_t childpid;
	PDIRECT *head = NULL;
	CHDIRECT predirect;

	predirect.s = getenv("HOME");
	head = linkedpath();
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		storetoken = NULL;

		predirect.boo = 0;
		counter++;
		write(STDOUT_FILENO, prompt, 4);
		i = 0;
		readnum = getline(&strinput, &len, stdin);
		if (readnum == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			__exit(errnum, storetoken, strinput, head, cmdinpath);
		}
		size = tokencount(strinput) + 1;

		if (size == 1)
			continue;
		token = _strtok(strinput, delim);

		storetoken = malloc(sizeof(char *) * size);
		storetoken[i++] = token;
		while (token != NULL)
		{
			token = _strtok(NULL, delim);
			storetoken[i++] = token;
		}
		i = 0;

		CDvalue = changedir(storetoken, &predirect);
		if (CDvalue  == -1)
			CDerrmessage(storetoken, argv[0], counter);
		childpid = fork();

		if (childpid == -1)
			__exit(errnum, storetoken, strinput, head, cmdinpath);

		if (childpid == 0)
		{
			errnum = checkexit(storetoken);
			if (errnum != -1)
				__exit(errnum, storetoken, strinput, head, cmdinpath);
			if (checkenv(storetoken))
				__exit(errnum, storetoken, strinput, head, cmdinpath);

			execve(storetoken[0], storetoken, NULL);
			cmdinpath = findcommand(head, storetoken[0]);
			execve(cmdinpath, storetoken, NULL);
			if (!predirect.boo)
				errmessage(storetoken, argv[0], counter);
			__exit(errnum, storetoken, strinput, head, cmdinpath);
		}
		else /** if childpid is more than 0 then we're in parent process*/
		{
			wait(NULL);
			errnum = checkexit(storetoken);
			if (errnum != -1)
				__exit(errnum, storetoken, strinput, head, cmdinpath);

		}
		if (storetoken)
			free(storetoken);
	}
	return (0);
}
