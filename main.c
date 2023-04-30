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
		write(1, "\n", 1);
		exit(0);
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
}

/**
 * main - the function
 * Return: 0 is ok
 */
int main(void)
{
	int res = 0;

	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);

	while (1)
	{
		res = isatty(STDIN_FILENO);
		if (res == 1)
			write(1, "($) ", 4);

		shellInt();
	}

	return (0);
}


