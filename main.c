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
			printf("($) ");

		shellInt();
	}

	return (0);
}

