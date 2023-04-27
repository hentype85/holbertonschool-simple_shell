#include "main.h"


int main(void)
{
	int res = 0;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTSTP, handle_sigstp);

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

void handle_sigint(int sig)
{
	(void) sig;
	putchar('\n');
	printf("($) ");
	fflush(stdout);
}

void handle_sigquit(int sig)
{
    char *msg = "Quit (core dumped)\n";
    size_t len;
    (void) sig;

    len = strlen(msg);

    if(write(STDERR_FILENO, msg, len) == -1)
       perror("write");

    exit(EXIT_SUCCESS);
}


void handle_sigstp(int sig)
{
	(void) sig;
	puts("\n");
	printf("($) ");
	fflush(stdout);
}
