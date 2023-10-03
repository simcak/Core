/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:17:14 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/03 18:16:11 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_child_process(char *argv[], char **envp, int *fd)
{
	char	**splited_argv;
	int		i;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	printf("we are here");
	// splited_argv = ft_split(argv[2], ' ');
	// execve("/nfs/homes/psimcak/bin/ls", splited_argv, envp);
}

void	ft_parent_process(char *argv[], char **envp, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execlp("grep", "grep", "rtt", NULL);
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
