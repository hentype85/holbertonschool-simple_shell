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

void executeCommand(char **bufferCopy);
void frees(char *buffer, char **bufferCopy);
char **getTokens(char *buffer, char **bufferCopy);
void shellInt(void);
void signalHandler(int signum);
char *_getenv();
char *_getpath(char *command);
void showEnviron(void);
int SpecialChar(char *s);

#endif


