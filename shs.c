#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 1024

/**
 * executeCommand - Function
 * @bufferCopy: the buffer
 * Return: the command being executed
 */
void executeCommand(char **bufferCopy)
{
	char command[SIZE];
	pid_t pid = fork();

	if (pid == 0)
	{
		snprintf(command, SIZE, "%s/%s", "/usr/bin", bufferCopy[0]);

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
		free(buffer), exit(0);
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
		{
			free(buffer);
			free(bufferCopy);
			exit(1);
		}
		else
		{
			executeCommand(bufferCopy);
		}
	}
	free(buffer);
	free(bufferCopy);
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
