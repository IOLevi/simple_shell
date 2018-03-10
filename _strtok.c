#include <stdio.h>
#include <stdlib.h>

char * _strtok(char *s, char *delim)
{
	int i = 0, delimit = 0, y = 0, x = 0, length = 0;
	static char *position;
	char *token;

	if (s == NULL)
	{
		position++;
		s = position;
	}
	else
		position = s;

	for ( length = 0; s[length] != '\0'; length++)
		;

	while (s[i] != '\0')
	{
		delimit = 0;

		while (delim[delimit] != '\0')
		{
			if (delim[delimit] == s[i])
			{
				s[i] = '\0';
				putchar(s[i]);
				break;
			}
			delimit++;
		}
		i++;
	}

	for (x = 0; s[x] != '\0'; x++)
		;

	token = malloc(sizeof(char) * x);

	if (token == NULL)
		return (0);

	x = 0;

	while (*position != '\0')
	{
		token[x] = *position;
		position++;
		x++;
	}

	printf("token: %s\n", token);
	return (token);
}

int main()
{
	char s[] = "Hi Evan, How are you?\n";
	char *delim = "  ";
	_strtok(s, delim);

	_strtok(NULL, delim);
	_strtok(NULL, delim);
	_strtok(NULL, delim);
	_strtok(NULL, delim);
	_strtok(NULL, delim);
	return (0);

}
