#include "main.h"

/**
 * showEnviron - list all the environment variables
 */
void showEnviron(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

