#include "main.h"

/**
 * signalHandler - the func of exit
 * @signum: the int of the signal
 */
void signalHandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n($) ", 6);
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

	while(1)
	{
		res = isatty(STDIN_FILENO);
		if (res == 1)
			write(1,"($) ",4);

		shellInt();
	}

	return (0);
}
