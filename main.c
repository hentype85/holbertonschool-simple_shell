#include "main.h"

void signalHandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n$ ", 4);
}


int main(int __attribute__((unused)) argc, char **argv)
{
	int isInteractive = 0;

	signal(SIGINT, signalHandler);

	while(1)
	{
		isInteractive = isatty(fileno(stdin));
		if (isInteractive == 1)
		{
			write(STDIN_FILENO,"$ ",2);
			shellInt(isInteractive, argv);
		}
		else
		{
		   shellInt(isInteractive, argv);
		}
	}

	return (0);
}
