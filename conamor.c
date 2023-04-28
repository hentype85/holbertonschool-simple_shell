#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 1024

extern char **environ;

void executeCommand(char *buffer, char **bufferCopy, char **argv);
char **getTokens(char *buffer, char **bufferCopy);
void signalHandler(int signum);
int _strncmp(char *s1, char *s2, int n);
char *_getenv();
char *_getpath(char *command);
void showEnviron(void);
int SpecialChar(char *s);
void shellInt(int isInteractive,char **argv);


void signalHandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n$ ", 4);
}


int main(int __attribute__((unused)) argc, char **argv)
{
	int isInteractive = 0;

	signal(SIGINT, signalHandler);

	while(1)
	{
		isInteractive = isatty(fileno(stdin));
		if (isInteractive == 1)
		{
			write(STDIN_FILENO,"$ ",2);
			shellInt(isInteractive, argv);
		}
		else
		{
		   shellInt(isInteractive, argv);
		}
	}

	return (0);
}

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

void shellInt(int isInteractive, char **argv)
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

void showEnviron(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

char *_getpath(char *command)
{
	int gotPath = 0;
	char command_path[SIZE];
	char *path = strdup(_getenv());
	char *token = strtok(path, ":");

	if (access(command, 1) == 0)
		return (strdup(command));
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
		return (strdup(command_path));

	return (NULL);
}

int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (s1[i] == s2[i] && i < n)
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}

	if (i == n)
		return (0);
	else
		return (s1[i] - s2[i]);
}


