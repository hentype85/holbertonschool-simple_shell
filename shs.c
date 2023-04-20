#include "main.h"

/**
 * executeCommand - Function
 * @bufferCopy: the buffer
 * @buffer: it is a buffer
 * Return: the command being executed
 */
void executeCommand(char *buffer, char **bufferCopy)
{
	char command[SIZE];
	pid_t pid = fork();

	if (pid == 0)
	{
		sprintf(command, "%s/%s", "/usr/bin", bufferCopy[0]);

		if (access(command, 1) == -1)
		{
			perror("hsh");
			frees(buffer, bufferCopy);
			exit(1);
		}

		if (execve(command, bufferCopy, NULL) == -1)
			perror("hsh");
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

/**
 * frees - free memory leaks
 * @buffer: address of pointer
 * @bufferCopy: address of double pointer
 */
void frees(char *buffer, char **bufferCopy)
{
	if (buffer)
		free(buffer);
	if (bufferCopy)
		free(bufferCopy);
}

/**
 * getTokens - string tokenization
 * @buffer: pointer to main buffer
 * @bufferCopy: double pointer to bufferCopy
 * Return: the string of tokens
 */
char **getTokens(char *buffer, char **bufferCopy)
{
	int i = 0;
	char *token = strtok(buffer, " \n");

	while (token != NULL)
	{
		bufferCopy[i++] = token;
		token = strtok(NULL, " \n");
	}
	bufferCopy[i] = NULL;

	return (bufferCopy);
}

/**
 * shell00 - its the shell
 */
void shell00(void)
{
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		printf("\n");
		frees(buffer, NULL), exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
			frees(buffer, bufferCopy), exit(1);
		else
			executeCommand(buffer, bufferCopy);
	}
	frees(buffer, bufferCopy);
}
