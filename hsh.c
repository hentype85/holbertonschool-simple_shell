#include "main.h"

/**
 * executeCommand - Function
 * @bufferCopy: the buffer tokenized
 * Return: the command being executed
 */
void executeCommand(char **bufferCopy)
{
	char command[SIZE];
	char *getPath = _getpath(bufferCopy[0]);
	pid_t pid;

	sprintf(command, "%s", getPath);

	if (access(command, 1) == -1)
	{
		perror("./hsh");
		return;
	}
	else
	{
		pid = fork();

		if (pid == 0)
		{
			if (execve(command, bufferCopy, environ) == -1)
			{
				perror("./hsh");
			}
		}
		else if (pid < 0)
		{
			perror("./hsh");
		}
		else
			waitpid(pid, NULL, 0);
	}

	free(getPath);
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
		if (SpecialChar(token) == 0)
			bufferCopy[i++] = token;

		token = strtok(NULL, " \n");
	}
	bufferCopy[i] = NULL;

	return (bufferCopy);
}

/**
 * shellInt - its the shell
 * @buffer: buffer for input
 * @bufferCopy: get the tokens
 * @bufSIZE: size of buffers
 */
void shellInt(char *buffer, char **bufferCopy, size_t bufSIZE)
{
	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		fflush(stdin);
		frees(buffer, bufferCopy), exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
		{
			frees(buffer, bufferCopy);
			exit(EXIT_SUCCESS);
		}

		if (strcmp(bufferCopy[0], "env") == 0)
			showEnviron();

		else
		{
			executeCommand(bufferCopy);
		}
	}
}


