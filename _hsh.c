#include "main.h"

/**
 *executeCommand - the function
 *@buffer: buffer
 *@bufferCopy: copy of the buffer
 *@argv: argv
 */
void executeCommand(char *buffer, char **bufferCopy, char **argv)
{
    char command[SIZE];
    pid_t pid;

    sprintf(command, "%s", _getpath(bufferCopy[0]));

    if (access(command, 1) == -1)
    {
	    perror(argv[0]);
	    return;
    }

    pid = fork();

        if (pid == 0)
        {
             /*bufferCopy[0][strlen(bufferCopy[0]) - 1] = '\0';*/

            if (execve(command, bufferCopy, NULL) == -1)
            {
                perror(argv[0]);
		free(buffer);
                free(bufferCopy);
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            perror(argv[0]);
	    free(buffer);
            free(bufferCopy);
            exit(EXIT_FAILURE);
        }
        else
        {
		waitpid(pid, NULL, 0);
        }
 
}
/**
 * getTokens - The function that tokenizes
 * @buffer: Object to tokenize
 * @bufferCopy: Tokenized copy
 * Return: Allways
 */
char **getTokens(char *buffer, char **bufferCopy)
{
	int i = 0;
	char *token = strtok(buffer, " \n\t");

	while (token != NULL)
	{
		bufferCopy[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	bufferCopy[i] = NULL;

	return (bufferCopy);
}

/**
 * shellInt - the core of the Shell
 * @buffer: The imput
 * @bufferCopy: The tokenized save
 * @bufSIZE: the size of the save
 * @argv: argv
 */
void shellInt(char *buffer, char **bufferCopy, size_t *bufSIZE, char **argv)
{
	if (getline(&buffer, bufSIZE, stdin) == -1)
	{
		free(buffer);/**/
		free(bufferCopy); /**/
		exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL) 
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
		{
			free(buffer);/**/
			free(bufferCopy);/**/
			exit(2);
		}

		if (strcmp(bufferCopy[0], "env") == 0)
		{
			showEnviron();
		}
		else
			executeCommand(buffer, bufferCopy, argv);
	}
}
