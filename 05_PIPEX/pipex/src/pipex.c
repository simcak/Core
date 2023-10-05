/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:17:14 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/05 07:21:59 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <string.h>
// i need to write strcat

void	ft_child_process(char *argv[], char **envp, int *fd)
{
	char	**splited_argv;
	char	**splited_path;
	char	*path;

	splited_argv = ft_split(argv[2], ' ');
	path = find_path(envp, splited_argv[0]);
	splited_path = ft_split(path, ':');

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(strcat(splited_path[5], "/ls"), splited_argv, envp);
}

void	ft_parent_process(char *argv[], char **envp, int *fd)
{
	char	**splited_argv;
	// int		i;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	splited_argv = ft_split(argv[3], ' ');
	execve("/usr/bin/grep", splited_argv, envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid_1;

	if (pipe(fd) == -1)
		ft_error("Error with PIPE");
	pid_1 = fork();
	if (pid_1 == -1)
		ft_error("Error with 1st FORK");
	if (pid_1 == 0)
		ft_child_process(argv, envp, fd);
	waitpid(pid_1, NULL, 0);
	ft_parent_process(argv, envp, fd);

	return (0);
}
