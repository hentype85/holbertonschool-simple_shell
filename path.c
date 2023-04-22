#include "main.h"

/**
 * _getpath - get the path
 * @command: command to check
 * Return: the command, pointer to path or NULL
 */
char *_getpath(char *command)
{
	int gotPath = 0;
	char command_path[SIZE];
	char *token = strtok(_getenv(), ":");

	if (access(command, 1) == 0)
		return (command);
	if (_getenv() != NULL)
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
	if (gotPath)
		return (strdup(command_path));

	return (NULL);
}
