#include "main.h"

/**
 * signalHandler - the function of signal
 * @signum: the int
 * Return: void
 */

int signalExit = 0;

void signalHandler(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 4);
	else if (signum == SIGQUIT)
	{
		signalExit = 1;
	}
}

/**
 *main - Main function
 *@argc: the content
 *@argv: the space
 *Return: allways
 */
int main(int __attribute__((unused)) argc, char **argv)
{
	int isInteractive = 0;
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);

	while (signalExit == 0)
	{
		isInteractive = isatty(fileno(stdin));
		if (isInteractive == 1)
		{
			write(STDIN_FILENO, "$ ", 2);
			shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
		else
		{
		   shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
	}

	return (0);
}
