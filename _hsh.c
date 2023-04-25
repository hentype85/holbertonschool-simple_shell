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

	/* sprintf(command, "%s/%s", "/usr/bin", bufferCopy[0]); */
	/* sprintf(command, "%s", bufferCopy[0]); */
	sprintf(command, "%s", getPath);

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
		if (pid == -1)
		{
	    		printf("Son proccess creation error.\n");
			exit(1);
		}
		else
			waitpid(pid, NULL, 0);
	}

	free(getPath);
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
	char *buffer;
	char **bufferCopy;

	buffer = malloc(sizeof(char) * bufSIZE);
	if (buffer == NULL)
	{
		perror("...Memory allocating error.\n");
		exit(1);
	}
	bufferCopy = malloc(sizeof(char *) * bufSIZE);
	if (bufferCopy == NULL)
	{
		perror("...Memory allocating error.\n");
		free(buffer), exit(1);
	}
	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		perror("...Imput lecture error.\n");
		frees(buffer, bufferCopy), exit(0);
	}
	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
			frees(buffer, bufferCopy), exit(0);

		if (strcmp(bufferCopy[0], "env") == 0)
			showEnviron();

		else if (bufferCopy != NULL)
			executeCommand(bufferCopy);
	}

	frees(buffer, bufferCopy);
}
