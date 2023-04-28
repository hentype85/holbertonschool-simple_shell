#include "main.h"

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
			write(STDIN_FILENO,"$ ",2);
			shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
		else
		{
		   shellInt(buffer, bufferCopy, &bufSIZE, argv);
		}
	}

	free(buffer);
	free(bufferCopy);

	return (0);
}
