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
		perror("./hsh No such file or directory");
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
	int readed = 0;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);
	if (bufferCopy == NULL)
		free(buffer);

	readed = getline(&buffer, &bufSIZE, stdin);
	if (readed == -1)
	{
		fflush(stdin);
		frees(buffer, bufferCopy), exit(0);
	}

	if (buffer[0] == '\0')
	{
		free(buffer);
		exit(0);
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

	frees(buffer, bufferCopy);
}
