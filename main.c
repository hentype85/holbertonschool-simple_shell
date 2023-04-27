#include "main.h"

/**
 * signalHandler - the func of exit
 * @signum: the int of the signal
 * Return: an int
 */
void signalHandler(int sig)
{
	char *prompt = "\n($) ";

	(void)sig;
	signal(SIGINT, signalHandler);
	write(STDIN_FILENO, prompt, 3);
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
		{
			printf("($) ");
			fflush(stdout);
		}

		shellInt();
	}

	return (0);
}

