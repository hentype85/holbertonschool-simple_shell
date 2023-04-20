#include "main.h"

/**
 * signalHandler - the func of exit
 * @signum: the int of the signal
 * Return: an int
 */
void signalHandler(int signum)
{
        exit(signum);
}

/**
 * main - the function
 * Return: nothing
 */
int main(void)
{
        signal(SIGINT, signalHandler);

        if (isatty(STDIN_FILENO) == 1)
        {
                while (1)
                {
                        printf("($) ");
                        shell00();
                }
        }
        return (0);
}
