#include "holberton.h"
/**
 * main - custom very lightweight shell
 * @argc: number of command line arguments
 * @argv: pointer to command line arguments
 * Return: 0
 */
int main(int argc __attribute__ ((unused)), char **argv)
{
	char *strinput = NULL, *token = NULL, **storetoken = NULL;
	char *cmdinpath = NULL, *delim = "\n ",  prompt[] = "($) ";
	int readnum, i = 0, errnum = 0, size = 0, counter = 0, CDvalue = 0;
	int  cerrnum = 0;
	size_t len = 0;
	pid_t childpid;
	PDIRECT *head = NULL;
	CHDIRECT predirect;

	predirect.s = _strdup(_getenv("HOME"));
	head = linkedpath();
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		storetoken = NULL;

		predirect.boo = 0;
		counter++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 4);
		i = 0;
		readnum = getline(&strinput, &len, stdin);
		if (readnum == -1)
		{
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
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

		/* builtins */
		CDvalue = changedir(storetoken, &predirect);
		if (CDvalue  == -1) /** CD into non exsistant directory */
			CDerrmessage(storetoken, argv[0], counter);

		/* fork for execve */
		childpid = fork();

		if (childpid == -1)
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);

		if (childpid == 0)
		{

			if (checkenv(storetoken)) /** checks to see if token is env */
				__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
			cerrnum = checkexit(storetoken); /** checks to see if token says  exit */
			if (cerrnum != -1)
				__exit(cerrnum, storetoken, strinput, head, cmdinpath, predirect.s);

			execve(storetoken[0], storetoken, environ);
			cmdinpath = findcommand(head, storetoken[0]);
			execve(cmdinpath, storetoken, environ);
			if (!predirect.boo) /** if CD happened */
				errmessage(storetoken, argv[0], counter);
			errnum = 0;
			__exit(errnum, storetoken, strinput, head, cmdinpath, predirect.s);
		}
		else /** if childpid is more than 0 then we're in parent process*/
		{
			wait(NULL);
			cerrnum = checkexit(storetoken); /** checks to see if token is exit */
			if (cerrnum != -1)
				__exit(cerrnum, storetoken, strinput, head, cmdinpath, predirect.s);

		}
		if (storetoken)
			free(storetoken);
	}
	return (0);
}
