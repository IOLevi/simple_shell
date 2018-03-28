#include "holberton.h"
/**
 * _itoa - converts integer to ascii
 * @i: number to convert
 * @t: pointer to space for the ascii string
 */
void _itoa(int i, char *t)
{
	int j;
	int rem = 0;
	int counter = 0;
	char temp;

	if (i == 0)
	{
		t[0] = '0';
		t[1] = '\0';
	}

	while (i != 0)
	{
		rem = i % 10;
		t[counter++] = rem + '0';
		i = i / 10;
	}

	for (j = 0; j < counter / 2; j++)
	{
		temp = t[j];
		t[j] = t[counter - 1 - j];
		t[counter - 1 - j] = temp;
	}

	t[counter] = '\0';

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
 *_strdup - duplicates a string
 *@s: string to duplicate
 *
 *Return: duplicated string
 */
char *_strdup(char *s)
{
	char *dup = NULL;
	unsigned int i, length = 0;

	length = _strlen(s);
	dup = malloc(sizeof(char) * length);
	for (i = 0; s[i] != '\0'; i++)
	{
		dup[i] = s[i];
	}
	return (dup);
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
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (-1);
}
/**
 * _atoi - converts string to integer
 * @s: string to convert
 * Return: -1 if it fails
 */
int _atoi(char *s) /** necessary for exit function when printing exit value*/
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
