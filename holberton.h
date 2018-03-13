#ifndef CESTLAVIE
#define CESTLAVIE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
/**
 * struct chdirect - struct to implement cd builtin
 * @s: directory path
 * @boo: boolean to indicate if cd was called
 */
typedef struct chdirect
{
	char *s;
	int boo;

} CHDIRECT;
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
extern char **environ;

int _strlen(char *s);
int _atoi(char *s);
void _itoa(int i, char *t);
char *_strdup(char *s);
int _strcmp(char *s1, char *s2);
int tokencount(char *s);
char * _strtok(char *s, char *delim);
PDIRECT *linkedpath(void);
char *findcommand(PDIRECT *head, char *commandinput);
void errmessage(char **c, char *p, int i);
void CDerrmessage(char **c, char *p, int i);
int changedir(char **p, CHDIRECT *predirect);
char *_getenv(const char *name);
int checkenv(char **p);
int checkexit(char **token);
void __exit(int errnum, char **p, char *getline, PDIRECT *head, char *findcommand);
#endif
