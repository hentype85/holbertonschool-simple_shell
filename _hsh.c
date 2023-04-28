#include "main.h"

/**
 * executeCommand - Function
 * @bufferCopy: the buffer tokenized
 * Return: the command being executed
 */
void executeCommand(char **bufferCopy)
{
	char command[SIZE];
	pid_t pid;

	/* sprintf(command, "%s/%s", "/usr/bin", bufferCopy[0]); */
	/* sprintf(command, "%s", bufferCopy[0]); */
	sprintf(command, "%s", _getpath(bufferCopy[0]));

	if (access(command, 1) == -1)
	{
		perror(bufferCopy[0]);
		return;
	}
	else
	{
		pid = fork();
		
		if (pid == 0)
		{
			bufferCopy[0][_strlen(bufferCopy[0]) - 1] = '\0';

			if (execve(command, bufferCopy, NULL) == -1)
			{
				perror(bufferCopy[0]);
			}
		}
		else if (pid < 0)
		{
			perror(bufferCopy[0]);
		}
		else
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
	if (buffer != NULL)
		free(buffer);
	if (bufferCopy != NULL)
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
 * shellInt - its the shell
 */
void shellInt(void)
{
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		printf("\n");
		frees(buffer, bufferCopy), exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
			frees(buffer, bufferCopy), exit(1);

		if (strcmp(bufferCopy[0], "env") == 0)
			showEnviron();
		else
			executeCommand(bufferCopy);
	}

	frees(buffer, bufferCopy);
}

