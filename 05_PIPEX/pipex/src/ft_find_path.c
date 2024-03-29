/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:58:42 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/06 19:12:10 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_find_paths(char **envp)
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

char	*ft_final_path(char **splited_paths, char **cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (splited_paths[i])
	{
		part_path = ft_strjoin(splited_paths[i], "/");
		path = ft_strjoin(part_path, cmd[0]);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
