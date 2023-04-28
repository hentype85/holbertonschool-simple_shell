#include "main.h"

/**
 * signalHandler - the function of signal
 * @signum: the int
 * Return: void
 */

void signalHandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
	fflush(stdout);
	exit(0);
}

/**
 * signalQuitHandler - the function of signal for SIGQUIT
 * @signum: the int
 * Return: void
 */

void signalQuitHandler(int signum)
{
        (void) signum;
        write(STDOUT_FILENO, "Ctrl+\\ pressed - exiting\n", 26);
        exit(0);
}

/**
 *main - Main function
 *@argc: the content
 *@argv: the space
 *Return: allways
 */
int main(int __attribute__((unused)) argc, char **argv)
{
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalQuitHandler);

	if (isatty(STDIN_FILENO) == 1)
	{
		while (1)
		{
			write(STDIN_FILENO, "$ ", 2);
			fflush(stdout);
			shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
	}
	else
	{
		while (1)
		{
			shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
	}

	return (0);
}
