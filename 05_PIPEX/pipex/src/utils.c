/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:01:08 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/06 19:38:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_array_of_strings(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_error_police(char *argv, char **envp)
{
	char	**splited_paths;
	char	**splited_argv;
	char	*all_paths;
	char	*path;

	all_paths = ft_find_paths(envp);
	splited_argv = ft_split(argv, ' ');
	splited_paths = ft_split(all_paths, ':');
	path = ft_final_path(splited_paths, splited_argv);
	ft_free_array_of_strings(splited_paths);
	ft_free_array_of_strings(splited_argv);
	if (path == 0)
	{
		if (path != NULL)
			free(path);
		return (0);
	}
	free(path);
	return (1);
}

void	ft_error(char *str)
{
	perror(str);
	exit(127);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
