/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdenek <zdenek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:49:12 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/17 16:55:31 by zdenek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#define BUFFER_SIZE_GNL 1

static char	*read_fd(int fd, char *s)
{
	char	*buff;
	int		pst_fd;

	pst_fd = 1;
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE_GNL + 1));
	if (!buff)
		return (NULL);
	while (ft_strchr_gnl(s, '\n') == NULL && pst_fd != 0)
	{
		pst_fd = read(fd, buff, BUFFER_SIZE_GNL);
		if (pst_fd == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[pst_fd] = '\0';
		s = ft_strjoin_gnl(s, buff);
	}
	free(buff);
	return (s);
}

static char	*process_current_line(char *s)
{
	char			*line;
	unsigned int	i;

	if (!s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*save_remainder_of_line(char *s)
{
	char			*rem;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	i++;
	rem = (char *) malloc(sizeof(char) * (ft_strlen_gnl(s) + 1 - i));
	if (!rem)
		return (NULL);
	j = 0;
	while (s[i])
		rem[j++] = s[i++];
	rem[j] = '\0';
	free(s);
	return (rem);
}

/**
 * @brief Reads a line from a file descriptor.
 * 
 * allocated memory for output must be freed.
 */
char	*ft_get_next_line(int fd)
{
	static char	*s[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE_GNL <= 0)
		return (NULL);
	s[fd] = read_fd(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	line = process_current_line(s[fd]);
	s[fd] = save_remainder_of_line(s[fd]);
	free(s[fd]);
	s[fd] = NULL;
	return (line);
}
