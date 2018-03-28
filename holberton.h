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
#endif
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