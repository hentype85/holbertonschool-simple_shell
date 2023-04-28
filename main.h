#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

#define SIZE 1024

extern char **environ;

void executeCommand(char *buffer, char **bufferCopy, char **argv);
char **getTokens(char *buffer, char **bufferCopy);
void signalHandler(int signum);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *s);
char *_getenv();
char *_getpath(char *command);
void showEnviron(void);
int SpecialChar(char *s);
void shellInt(char *buffer, char **bufferCopy, size_t *bufSIZE, char **argv);

#endif
