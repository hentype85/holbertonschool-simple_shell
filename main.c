#include "main.h"

/**
 * signalHandler - the func of exit
 * @signum: the int of the signal
 * Return: an int
 */
void signalHandler(int __attribute__((unused)) signum)
{
	printf("\n");
	fflush(stdout);
	exit(0);
}

/**
 * main - the function
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 is ok
 */
int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	signal(SIGINT, signalHandler);

	if (isatty(STDIN_FILENO) == 1)
	{
		while (1)
		{
			printf("($) ");
			fflush(stdout);
			shellInt();
		}
	}
	else
	{
		while (1)
		{
			shellInt();
		}
	}
}
