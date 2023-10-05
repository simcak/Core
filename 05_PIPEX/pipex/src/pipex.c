/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:17:14 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/05 14:45:13 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_child_process(char *argv[], char **envp, int *fd)
{
	char	**splited_argv;
	char	**splited_paths;
	char	*all_paths;
	char	*path;
	int		fd_in;

	close(fd[0]);
	fd_in = open(argv[1], O_RDONLY, 0444);
	if (fd_in == -1)
		ft_error("child's OPEN error");
	all_paths = ft_find_paths(envp);
	splited_argv = ft_split(argv[2], ' ');
	splited_paths = ft_split(all_paths, ':');
	path = ft_final_path(splited_paths, splited_argv);
	ft_free_array_of_strings(splited_paths);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd_in);
	if (execve(path, splited_argv, envp) == -1)
		ft_error("EXECVE failed");
}

void	ft_parent_process(char *argv[], char **envp, int *fd)
{
	char	**splited_argv;
	char	**splited_paths;
	char	*all_paths;
	char	*path;
	int		fd_out;

	close(fd[1]);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		ft_error("parent's OPEN error");
	all_paths = ft_find_paths(envp);
	splited_argv = ft_split(argv[3], ' ');
	splited_paths = ft_split(all_paths, ':');
	path = ft_final_path(splited_paths, splited_argv);
	ft_free_array_of_strings(splited_paths);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd_out);
	if (execve(path, splited_argv, envp) == -1)
		ft_error("EXECVE failed");
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid_1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error("Error with PIPE");
		pid_1 = fork();
		if (pid_1 == -1)
			ft_error("Error with 1st FORK");
		if (pid_1 == 0)
			ft_child_process(argv, envp, fd);
		waitpid(pid_1, NULL, 0);
		ft_parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
