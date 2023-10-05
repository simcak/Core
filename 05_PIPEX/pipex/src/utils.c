/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:01:08 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/05 07:18:09 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// char	*ft_find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;
// 	char	*part_path;

// 	i = 0;
// 	while (ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	paths = ft_split(envp[i] + 5, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, cmd);
// 		free(part_path);
// 		if (access(path, F_OK) == 0)
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	i = -1;
// 	while (paths[++i])
// 		free(paths[i]);
// 	free(paths);
// 	return (0);
// }
char	*ft_find_path(char **envp)
{
	char	*path;
	int		i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = envp[i] + 5;
			return (path);
		}
		i++;
	}
	return (0);
}

// void	ft_execute(char *argv, char **envp)
// {
// 	char	**cmd;
// 	int 	i;
// 	char	*path;
	
// 	i = 0;
// 	cmd = ft_split(argv, ' ');
// 	path = ft_find_path(cmd[0], envp);
// 	if (!path)	
// 	{
// 		while (cmd[i])
// 			free(cmd[i++]);
// 		free(cmd);
// 		ft_error("Error with PATH");
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 		ft_error("EXECVE failed");
// }

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
