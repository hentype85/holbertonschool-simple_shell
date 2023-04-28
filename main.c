#include "main.h"

/**
 * signalHandler - the function of signal
 * @signum: the int
 * Return: void
 */

void signalHandler(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 4);
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
	isInteractive = isatty(fileno(stdin));

	while (1)
	{
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
