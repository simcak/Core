## This is a Fork from [Pasqualerossi Exam-Rank-04](https://github.com/pasqualerossi/42-School-Exam-Rank-04) modified to be a little more readable in exchange to be a little longer than the original.
# Exam Question

This exam has 1 question, microshell:

- [Microshell.c](https://github.com/pasqualerossi/42-School-Exam-Rank-04/blob/main/microshell.c)

if you can make this code shorter, but readable, let me know!

<br>

## Excepted Files

- microshell.c

## Subject Text

Allowed functions: 

> malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp


## The Program
Write a program that will behave like executing a shell command

- The command line to execute will be the arguments of this program

- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)

- You must implement "|" and ";" like in bash
	- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"

- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
	- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
	- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
	- a cd command will never be immediately followed or preceded by a "|"

- You don't need to manage any type of wildcards (*, ~ etc...)

- You don't need to manage environment variables ($BLA ...)

- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit

- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)

- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.

## Example

for example this should work:
```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

>./microshell 
```

## Hints
- Don't forget to pass the environment variable to execve
- Do not leak file descriptors!

## Commented Code

```c
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

// Here we are defining all error messages that we are gonna need for the microshell
#define ERROR_FATAL	"error: fatal\n"
#define BAD_EXEC	"error: cannot execute "
#define BAD_ARGS	"error: cd: bad arguments\n"
#define BAD_DIRE	"error: cd: cannot change directory to "

// Prints the error message and returns a 1 directly to show an error occurring
int	print_error(char *error_msg)
{
	while (*error_msg)
		write(2, error_msg++, 1);
	return (1);
}

// A wrapper to print_error to print complementary info and a new line at the end
int	print_error_info(char *str1, char *str2)
{
	print_error(str1);
	print_error(str2);
	return (write(2, "\n", 1));
}

int	cd(char **argv, int delimiter)
{
	if (delimiter != 2)									// Checks the amount of arguments
		return (print_error(BAD_ARGS));					// Return with an error message stating that the arguments are wrong
	if (chdir(argv[1]) == -1)							// Changes the directory and check if an error occurs
		return (print_error_info(BAD_DIRE, argv[1]));	// If there was an error print the error message
	return (0);
}

void	set_pipe(bool has_pipe, int *pipe_fd, int end)
{
	if (has_pipe == true					// Checks if the command contains a pipe
		&& (dup2(pipe_fd[end], end) == -1	// If so duplicates the pipe end to the standard end and checks for error
			|| close(pipe_fd[0]) == -1		// Closes the now unused pipe ends and checks for errors
			|| close(pipe_fd[1]) == -1))
		exit(print_error(ERROR_FATAL));		// If any error appears exit with the fatal error message
}

int	exec(char **argv, int delimiter, char **envp)
{
	const bool	has_pipe = argv[delimiter]				// It checks if there is a delimiter
		&& !strcmp(argv[delimiter], "|");				// and if it is a pipe.
	int			pipe_fd[2];
	int			pid;
	int			status;

	if (!has_pipe && !strcmp(*argv, "cd"))				// If there is not a pipe and our command is cd
		return (cd(argv, delimiter));					// It executes cd
	if (has_pipe && pipe(pipe_fd) == -1)				// If there is a Pipe it creates the pipe and check that the creation was a success
		exit(print_error(ERROR_FATAL));
	if ((pid = fork()) == -1)							// Creates the fork and checks for errors in its creation
		exit(print_error(ERROR_FATAL));
	if (!pid)											// If pid == 0 it is the child process
	{
		argv[delimiter] = NULL;							// The delimiter is set to NULL, that way any function that uses the arguments, can't look pass the delimiter
		set_pipe(has_pipe, pipe_fd, STDOUT_FILENO);		// Sets the pipe to output information
		if (!strcmp(*argv, "cd"))						// If the command is cd
			exit(cd(argv, delimiter));					// Exit with the exit code generated by executing cd.
		execve(*argv, argv, envp);						// Any other command is executed by Execve
		exit(print_error_info(BAD_EXEC, *argv));		// If the execution failed exit with the error message informing what it tried to execute
	}
	set_pipe(has_pipe, pipe_fd, STDIN_FILENO);			// In the main proccess prepare the pipe to Read from the input side
	waitpid(pid, &status, 0);							// Wait for the child to execute and save its status
	return (WIFEXITED(status) && WEXITSTATUS(status));	// Check if it exited normally and return its exit status
}

int	get_delimiter_index(char **argv)
{
	int	delimiter;

	delimiter = 0;
	while (argv[delimiter]					// Create a loop checking if there is still a string
		&& strcmp(argv[delimiter], "|")		// If that string is not a Pipe
		&& strcmp(argv[delimiter], ";"))	// and that it is not a semicolon either
		delimiter++;						// Advance through the loop
	return (delimiter);						// return the index where there is no more strings or you found a pipe / semicolon
}

int	main(int argc, char **argv, char **envp)
{
	int			delimiter;
	static int	status = 0;							// Set the default status in case nothing is executed to 0

	delimiter = 0;
	while (argc > 1 && argv[delimiter])				// Loop while the arguments given were at least 1 and we still have arguments to loop through
	{
		argv += delimiter + 1;						// Jump over the delimiter / first argument (the exucutable path / name)
		delimiter = get_delimiter_index(argv);		// Get the index of the next delimiter (NULL, ';', '|')
		if (delimiter)								// If there is a command between delimiters
			status = exec(argv, delimiter, envp);	// execute it and save the status
	}
	return (status);								// return the status of the last execution
}
```

## Exam Practice Tool

Practice the exam just like you would in the real exam - https://github.com/JCluzet/42_EXAM
