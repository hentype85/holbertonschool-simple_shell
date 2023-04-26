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
	int res = 0;

	signal(SIGINT, signalHandler);

	while (1)
	{
		res = isatty(STDIN_FILENO);
		if (res == 1)
			printf("($) ");

		shellInt();
	}

	return (0);
}
