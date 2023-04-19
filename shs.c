#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1024

void executeCommand(char **bufferCopy)
{
    	char command[SIZE]; 
    	pid_t pid = fork(); //crear proceso hijo

    	if (pid == 0) 
    	{   //proceso hijo
		snprintf(command, SIZE, "%s/%s", "/usr/bin", bufferCopy[0]);
        
		if (execve(command, bufferCopy, NULL) == -1) 
		{
	     		perror("hsh");
		}
    	} 
    	else if (pid < 0) 
    	{ //error fork
		perror("hsh");
    	} 
    	else 
    	{ // proceso padre
		waitpid(pid, NULL, 0); // esperar que termine el hijo
    	}
}

int shell00()
{
     	size_t len = 0, bufSIZE = SIZE;
     	int i = 0, exVal = 0;
     	char *buffer = malloc(sizeof(char) * bufSIZE); //asignar memoria
   
     	char **bufferCopy;
     	char *token;
     	pid_t pid;
   
     	if (getline(&buffer,&bufSIZE,stdin) == -1)
     	{
	  	printf("\n");
	  	free(buffer), exit(0);
     	}
   
 
     	//tokens
	bufferCopy = malloc(sizeof(char *) * bufSIZE);
     	token = strtok(buffer, " \n");
     	while (token != NULL)
     	{
	  	bufferCopy[i++] = token;
	  	token = strtok(NULL, " \n");
     	}
     	bufferCopy[i] = NULL; //NULL al final del token
   
   
     	//ejecutar comando
	if(bufferCopy[0] != NULL)
     	{
	  	if (strcmp(bufferCopy[0], "exit") == 0)
	  	{
	       		free(buffer);
	       		free(bufferCopy);
	       		return (1);
	  	}
	  	else
	  	{
	       		executeCommand(bufferCopy);
	  	}      
     	}   
     	free(buffer);
     	free(bufferCopy);
}

void signalHandler(int signum)
{
     	exit(1);
}

int main() 
{

     	signal(SIGINT, signalHandler);  //ctrl+d cierra programa

     	if (isatty(STDIN_FILENO) == 1) //si el stdout esta conectado al terminal
     	{
	  	while (1)
	  	{
	       		printf("($) ");
	       		if (shell00() == 1)
		    		break;
	  	}
	}
     	return 0;
}
