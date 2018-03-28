#include "holberton.h"

/**
 * main - custom very lightweight shell
 * @arc: number of command line arguments
 * @argv: pointer to command line arguments
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *strinput = NULL, *token = NULL, **storetoken = NULL, prompt[] = "($) ";
	char *cmdinpath = NULL, *delim = " \n";
	int readnum, i = 0, errnum = 0, size = 0, counter = 0;
	size_t len = 0;
	pid_t childpid;
	PDIRECT *head = NULL;
	CHDIRECT predirect;

	predirect.s = getenv("HOME");
	head = linkedpath(); /** link list of the entire path */
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (storetoken)
			free(storetoken);
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
		{
			//free(strinput);
			continue;
		}
		token = _strtok(strinput, delim);

		storetoken = malloc(sizeof(char *) * size);
		storetoken[i++] = token;
		while (token != NULL)
		{
			token = _strtok(NULL, delim);
			storetoken[i++] = token;
		}
		i = 0;
		changedir(storetoken, &predirect);

		childpid = fork();

		if (childpid == -1)
			__exit(errnum, storetoken, strinput, head, cmdinpath);

		if (childpid == 0)
		{

			if ((errnum = checkexit(storetoken)) != -1)
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

			if ((errnum = checkexit(storetoken)) !=-1)
			{

				__exit(errnum, storetoken, strinput, head, cmdinpath);
		       	}

		}
	}
	return (0);
}
