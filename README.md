<h1 align ="center">C - Simple Shell</h1><br>
<p align="center">
  <img width="500" height="300" src="https://media.istockphoto.com/id/508578343/photo/seashell-on-the-beach.jpg?s=612x612&w=0&k=20&c=-AexzU9LyyrC_0FjAPDcfQjK8h5K6EqFdp_DfLvTBl8=">
</p>


A simple shell written in C that has some basic functionality for executing commands on a Unix operating system.
The shell is capable of executing interactive and non-interactive commands.

# Functions
executeCommand
executes the commands entered by stdin.
This function receives as arguments a pointer to a buffer, which contains the command to execute, and a pointer to a copy of the buffer,
which is used to get the command tokens. It also receives a pointer to a string array containing the command's arguments.

getTokens
gets the tokens from the command entered by the user.
This function receives as arguments a pointer to a buffer containing the command,
and a pointer to a copy of the buffer. Returns a pointer to a string array containing the tokens.

signalHandler
handles the signals that are received in the shell.
In particular, this function handles the SIGINT signal, which is sent when the user presses Ctrl + D.

SpecialChar checks if a string has any special characters and returns 1 
if it finds any and 0 if none is found.

_getenv 
gets the value of an environment variable.
This function receives as argument the name of the environment variable,
and returns a pointer to a string containing the value of the variable.

_getpath 
gets the full path of an external command.
This function receives as argument the name of the command,
and returns a pointer to a string containing the full path of the command.

showEnviron 
displays the environment variables available on the system.

shellInt initialize the shell and read the commands entered by the user.
This function receives as arguments a pointer to the command buffer, a pointer to the copy of the buffer,
a pointer to the size of the buffer, and a pointer to the string array containing the command arguments.

# functions and system calls used
**strings.h** library
**access** (man 2 access)
**execve** (man 2 execve)
**exit** (man 3 exit)
**fflush** (man 3 fflush)
**fork** (man 2 fork)
**free** (man 3 free)
**getline** (man 3 getline)
**isatty** (man 3 isatty)
**malloc** (man 3 malloc)
**perror** (man 3 perror)
**printf** (man 3 printf)
**sprintf** (man 3 sprintf)
**signal** (man 2 signal)
**strtok** (man 3 strtok)
**waitpid** (man 2 waitpid)
**write** (man 2 write)

# Compilation
```c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
# Valgrind
```c
valgrind --leak-check=full --show-leak-kinds=all echo "/bin/ls -l" | ./hsh
```
