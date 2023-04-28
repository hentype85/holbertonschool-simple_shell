#include "main.h"

/**
 * _getenv - get path
 * Return: pointer to string
 */
char *_getenv()
{
	char *env, *value = NULL, *path = "PATH";
	int i = 0, lenPath = 0;

	while (path[lenPath])
		lenPath++;

	while (environ[i])
	{
		env = environ[i];

		if (_strncmp(path, env, lenPath) == 0)
		{
			env += lenPath + 1;
			value = env;
			break;
		}

		i++;
	}

	return (value);
}

