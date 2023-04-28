# C - Simple Shell

A simple shell written in C that has some basic functionality for executing commands on a Unix operating system.
The shell is capable of executing interactive and non-interactive commands.

# Functions
executeCommand() executes the commands entered by stdin.
This function receives as arguments a pointer to a buffer, which contains the command to execute, and a pointer to a copy of the buffer,
which is used to get the command tokens. It also receives a pointer to a string array containing the command's arguments.

getTokens() gets the tokens from the command entered by the user.
This function receives as arguments a pointer to a buffer containing the command,
and a pointer to a copy of the buffer. Returns a pointer to a string array containing the tokens.

signalHandler() handles the signals that are received in the shell.
In particular, this function handles the SIGINT signal, which is sent when the user presses Ctrl + D.

_strncmp() compares two character strings.
This function receives as arguments two pointers to character strings, and an integer indicating the number of characters to compare.
Returns an integer indicating whether the strings are equal to 0, or different to 1.

_strdup() duplica una cadena de caracteres. 
Esta función recibe como argumento un puntero a una cadena de caracteres, 
y devuelve un puntero a una nueva cadena de caracteres que contiene una copia de la cadena original.

_getenv() gets the value of an environment variable.
This function receives as argument the name of the environment variable,
and returns a pointer to a string containing the value of the variable.

_getpath() gets the full path of an external command.
This function receives as argument the name of the command,
and returns a pointer to a string containing the full path of the command.

showEnviron() displays the environment variables available on the system.

shellInt() initialize the shell and read the commands entered by the user.
This function receives as arguments a pointer to the command buffer, a pointer to the copy of the buffer,
a pointer to the size of the buffer, and a pointer to the string array containing the command arguments.

# Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh



