#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 1024

extern char **environ;

void executeCommandar(char **bufferCopy);
void frees(char *buffer, char **bufferCopy);
char **getTokens(char *buffer, char **bufferCopy);
void shellInt(void);
void signalHandler(int signum);
int _strncmp(char *s1, char *s2, int n);
char *_getenv();

#endif
