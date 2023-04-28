#include "main.h"

void signalHandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n$ ", 4);
}


int main(int __attribute__((unused)) argc, char **argv)
{
	int isInteractive = 0;
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	signal(SIGINT, signalHandler);

	while (1)
	{
		isInteractive = isatty(fileno(stdin));
		if (isInteractive == 1)
		{
			write(STDIN_FILENO,"$ ",2);
			shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
		else
		{
		   shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
	}

	return (0);
}
