/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:41:02 by JFikents          #+#    #+#             */
/*   Updated: 2025/01/14 18:49:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define ERROR_FATAL	"error: fatal\n"
#define BAD_EXEC	"error: cannot execute "
#define BAD_ARGS	"error: cd: bad arguments\n"
#define BAD_DIRE	"error: cd: cannot change directory to "

int	print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
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
		return (print_error(BAD_ARGS));
	if (chdir(argv[1]) == -1)
		return (print_error_info(BAD_DIRE, argv[1]));
	return (0);
}

void	set_pipe(bool has_pipe, int *pipe_fd, int end)
{
	if (has_pipe == true
		&& (dup2(pipe_fd[end], end) == -1
			|| close(pipe_fd[0]) == -1
			|| close(pipe_fd[1]) == -1))
		exit(print_error(ERROR_FATAL));
}

int	exec(char **argv, int delimiter, char **envp)
{
	const bool	has_pipe = argv[delimiter] && !strcmp(argv[delimiter], "|");
	int			pipe_fd[2];
	int			pid;
	int			status;

	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, delimiter));
	if ((has_pipe && pipe(pipe_fd) == -1) || ((pid = fork()) == -1))
		exit(print_error(ERROR_FATAL));
	if (!pid)
	{
		argv[delimiter] = NULL;
		set_pipe(has_pipe, pipe_fd, STDOUT_FILENO);
		if (!strcmp(*argv, "cd"))
			exit(cd(argv, delimiter));
		execve(*argv, argv, envp);
		exit(print_error_info(BAD_EXEC, *argv));
	}
	set_pipe(has_pipe, pipe_fd, STDIN_FILENO);
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	get_delimiter_index(char **argv)
{
	int	delimiter;

	delimiter = 0;
	while (argv[delimiter]
		&& strcmp(argv[delimiter], "|")
		&& strcmp(argv[delimiter], ";"))
		delimiter++;
	return (delimiter);
}

int	main(int argc, char **argv, char **envp)
{
	int			delimiter;
	static int	status = 0;

	delimiter = 0;
	while (argc > 1 && argv[delimiter])
	{
		argv += delimiter + 1;
		delimiter = get_delimiter_index(argv);
		if (delimiter)
			status = exec(argv, delimiter, envp);
	}
	return (status);
}
