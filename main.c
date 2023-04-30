#include "main.h"

/**
 * signalHandler - the func of exit
 * @sig: the int of the signal
 * Return: an int
 */
void signalHandler(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("\n");
	}
	else if (sig == SIGINT)
	{
		printf("\n");
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
 * main - the function
 * Return: 0 is ok
 */
int main(void)
{
	int res = 0;
	size_t bufSIZE = SIZE;
	char *buffer;
	char **bufferCopy;

	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);

	while (1)
	{
		res = isatty(STDIN_FILENO);
		if (res == 1)
			printf("($) ");

		buffer = malloc(sizeof(char) * bufSIZE);
		bufferCopy = malloc(sizeof(char) * bufSIZE);

		shellInt(buffer, bufferCopy, bufSIZE);

		frees(buffer, bufferCopy);
	}
	return (0);
}

