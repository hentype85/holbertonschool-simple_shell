#include "main.h"

/**
 * frees - Function for executing
 * @buffer: The Buffer
 * @bufferCopy: a Saved copy of the Buffer
 */
void frees(char *buffer, char **bufferCopy)
{
	if (buffer != NULL)
		free(buffer);
	if (bufferCopy != NULL)
		free(bufferCopy);
}

/**
 *executeCommand - the function
 *@buffer: buffer
 *@bufferCopy: copy of the buffer
 *@argv: argv
 */
void executeCommand(char *buffer, char **bufferCopy, char **argv)
{
	char command[SIZE];
	char *getPath = _getpath(bufferCopy[0]);
	int status = 0;
	pid_t pid;

	sprintf(command, "%s", getPath);
	if (access(command, 1) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			bufferCopy[0][strlen(bufferCopy[0]) - 1] = '\0';
			if (execve(command, bufferCopy, NULL) == -1)
			{
				perror(argv[0]);
				free(getPath);
				free(buffer);
				free(bufferCopy);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
		{
			perror(argv[0]);
			free(getPath);
			free(buffer);
			free(bufferCopy);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (waitpid(-1, &status, 0) == -1)
				perror(argv[0]);
			else
			{
				perror(argv[0]);
				free(getPath);
				return;
			}
		}
	}
		free(getPath);

		if (execve(command, bufferCopy, NULL) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			{
				if (waitpid(-1, &status, 0) == -1)
					perror(argv[0]);
			}
		}
		else
		{
			perror(argv[0]);
			return;
		}
		free(getPath);
}
/**
 * getTokens - The function that tokenizes
 * @buffer: Object to tokenize
 * @bufferCopy: Tokenized copy
 * Return: Allways
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
 * shellInt - the core of the Shell
 * @buffer: The imput
 * @bufferCopy: The tokenized save
 * @bufSIZE: the size of the save
 * @argv: argv
 */
void shellInt(char *buffer, char **bufferCopy, size_t *bufSIZE, char **argv)
{
	if (getline(&buffer, bufSIZE, stdin) == -1)
	{
		frees(buffer, bufferCopy);
		exit(1);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
		{
			frees(buffer, bufferCopy);
			exit(0);
		}

		if (strcmp(bufferCopy[0], "env") == 0)
		{
			showEnviron();
		}
		else
			executeCommand(buffer, bufferCopy, argv);
	}

	frees(buffer, bufferCopy);
}
