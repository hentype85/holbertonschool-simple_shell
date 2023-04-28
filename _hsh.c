#include "main.h"

void executeCommand(char *buffer, char **bufferCopy, char **argv)
{
    char command[SIZE];
    char *getPath = _getpath(bufferCopy[0]);
    int status = 0;
    pid_t pid;

    sprintf(command, "%s", getPath);

    if (access(command, 1) == 0)
    {
        pid = fork();

        if (pid == 0)
        {
            bufferCopy[0][strlen(bufferCopy[0]) - 1] = '\0';

            if (execve(command, bufferCopy, NULL) == -1)
            {
                perror(argv[0]);
                free(getPath);
		free(buffer);
                free(bufferCopy); 
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            perror(argv[0]);
            free(getPath);
	    free(buffer);
            free(bufferCopy);
            exit(EXIT_FAILURE);
        }
        else
        {
            if (waitpid(-1, &status, 0) == -1)
                perror(argv[0]);
        }
    }
    else
    {
        perror(argv[0]);
        free(getPath);
	free(buffer);
        free(bufferCopy);
        return;
    }

    free(getPath);
    free(buffer);
    free(bufferCopy);
}

char **getTokens(char *buffer, char **bufferCopy)
{
	int i = 0;
	char *token = strtok(buffer, " \n");

	while (token != NULL)
	{
		bufferCopy[i++] = token;
		token = strtok(NULL, " \n");
	}
	bufferCopy[i] = NULL;

	return (bufferCopy);
}

void shellInt(int __attribute__((unused)) isInteractive, char **argv)
{
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		free(buffer);/**/
		free(bufferCopy); /**/
		exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL) {
		if (strcmp(bufferCopy[0], "exit") == 0)
		{
			free(buffer);/**/
			free(bufferCopy);/**/
			exit(1);
		}

		if (strcmp(bufferCopy[0], "env") == 0)
			showEnviron();
		else
			executeCommand(buffer, bufferCopy, argv);
	}
}
