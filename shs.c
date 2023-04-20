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
		{
			perror("hsh");
		}
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
 * shell00 - its the shell
 * Return: void
 */
int shell00(void)
{
	size_t len = 0, bufSIZE = SIZE;
	int i = 0, exVal = 0;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy;
	char *token;
	pid_t pid;

	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		printf("\n");
		frees(buffer, NULL), exit(0);
	}

	bufferCopy = malloc(sizeof(char *) * bufSIZE);
	token = strtok(buffer, " \n");
	while (token != NULL)
	{
		bufferCopy[i++] = token;
		token = strtok(NULL, " \n");
	}
	bufferCopy[i] = NULL;

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
			frees(buffer, bufferCopy), exit(1);
		else
			executeCommand(buffer, bufferCopy);
	}
	frees(buffer, bufferCopy);
}

/**
 * signalHandler - the func of exit
 * @signum: the int of the signal
 * Return: an int
 */
void signalHandler(int signum)
{
	exit(1);
}

/**
 * main - the function
 * Return: nothing
 */
int main(void)
{
	signal(SIGINT, signalHandler);

	if (isatty(STDIN_FILENO) == 1)
	{
		while (1)
		{
			printf("($) ");
			if (shell00() == 1)
				break;
		}
	}
	return (0);
}
