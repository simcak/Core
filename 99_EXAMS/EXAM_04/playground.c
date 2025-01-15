#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int	print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (EXIT_FAILURE);
}

int	print_error_info(char *str1, char *str2)
{
	print_error(str1);
	print_error(str2);
	return (write(2, "\n", 1));
}

int	cd(char **argv, int delimiter)
{
	if (delimiter != 2)
		return (print_error("error: cd: bad arguments\n"));
	if (chdir(argv[1]) == -1)
		return (print_error_info("error: cd: cannot change directory to ", argv[1]));
	return (EXIT_SUCCESS);
}

void	set_pipe(bool has_pipe, int *pipe_fd, int end)
{
	if (has_pipe && (dup2(pipe_fd[end], end) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
		exit(print_error("error: fatal\n"));
}

int	exec(char **argv, int delimiter, char **envp)
{
	int			status;
	int			pid;
	int			pipe_fd[2];
	const bool	has_pipe = argv[delimiter] && strcmp(argv[delimiter], "|") == 0;

	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, delimiter));
	if ((has_pipe && pipe(pipe_fd) == -1) || ((pid = fork()) == -1))
		exit(print_error("error fatal\n"));
	if (!pid)
	{
		argv[delimiter] = NULL;
		set_pipe(has_pipe, pipe_fd, STDOUT_FILENO);
		if (!strcmp(*argv, "cd"))
			exit(cd(argv, delimiter));
		execve(*argv, argv, envp);
		exit(print_error_info("error: cannot execute ", *argv));
	}
	set_pipe(has_pipe, pipe_fd, STDIN_FILENO);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	get_delimiter(char **argv)
{
	int	delimiter = 0;

	while (argv[delimiter] && strcmp(argv[delimiter], "|") && strcmp(argv[delimiter], ";"))
		delimiter++;
	return (delimiter);
}

int	main(int argc, char **argv, char **envp)
{
	int			delimiter = 0;
	static int	status = 0;

	while (argv[delimiter] && argc > 1)
	{
		argv += delimiter + 1;
		delimiter = get_delimiter(argv);
		if (delimiter)
			status = exec(argv, delimiter, envp);
	}
	return (status);
}
