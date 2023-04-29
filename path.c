#include "main.h"

/**
 * _getpath - get the rute of command
 * finding the ":" as a delimiter
 * @command: command to check
 * Return: the command, pointer to path or NULL
 */
char *_getpath(char *command)
{
	int gotPath = 0;
	char command_path[SIZE];
	char *path = strdup(_getenv());
	char *token = strtok(path, ":");

	if (access(command, 1) == 0)
		return (_strdup(command));
	if (path != NULL)
	{
		while (token != NULL)
		{
			sprintf(command_path, "%s/%s", token, command);

			if (access(command_path, 1) == 0)
			{
				gotPath = 1;
				break;
			}
			token = strtok(NULL, ":");
		}
	}

	free(path);

	if (gotPath)
		return (_strdup(command_path));

	return (NULL);
}
