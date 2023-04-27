#include "main.h"

/**
 * executeCommand - Function
 * @buffer: original buffer
 * @bufferCopy: the buffer tokenized
 * Return: the command being executed
 */
void executeCommand(char *buffer, char **bufferCopy)
{
        char command[SIZE];
        char **getPath = malloc(sizeof(char *) * 2);
	int status = 0;
        pid_t pid;

        getPath[0] = _getpath(bufferCopy[0]);
        getPath[1] = NULL;

        if (!getPath[0])
        {
                perror("not found");
                free(getPath); 
                return;
        }

        sprintf(command, "%s", getPath[0]);

        pid = fork();

        if (pid == -1)
        {
                perror(bufferCopy[0]);
                free(getPath);
		return;
        }
        else if (pid == 0)
        {
                if (execve(command, bufferCopy, getPath) == -1)
                {
                        perror(bufferCopy[0]);
                        frees(buffer,bufferCopy);
                        free(getPath); 
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                while (!WIFEXITED(status) && !WIFSIGNALED(status))
                                waitpid(pid, &status, WUNTRACED);
        }

        free(getPath);
}

/**
 * frees - free memory leaks
 * @buffer: address of pointer
 * @bufferCopy: address of double pointer
 */
void frees(char *buffer, char **bufferCopy)
{
	if (buffer != NULL)
		free(buffer);
	if (bufferCopy != NULL)
		free(bufferCopy);
}

/**
 * getTokens - string tokenization
 * @buffer: pointer to main buffer
 * @bufferCopy: double pointer to bufferCopy
 * Return: the string of tokens
 */
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

/**
 * shellInt - its the shell
 */
void shellInt(void)
{
	size_t bufSIZE = SIZE;
	char *buffer = malloc(sizeof(char) * bufSIZE);
	char **bufferCopy = malloc(sizeof(char *) * bufSIZE);

	if (getline(&buffer, &bufSIZE, stdin) == -1)
	{
		frees(buffer, bufferCopy), exit(0);
	}

	bufferCopy = getTokens(buffer, bufferCopy);

	if (bufferCopy[0] != NULL)
	{
		if (strcmp(bufferCopy[0], "exit") == 0)
			frees(buffer, bufferCopy), exit(1);

		if (strcmp(bufferCopy[0], "env") == 0)
			showEnviron();
		else
			executeCommand(buffer, bufferCopy);
	}

	frees(buffer, bufferCopy);
}
