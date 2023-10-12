/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:07:45 by lwoiton           #+#    #+#             */
/*   Updated: 2023/07/07 23:11:41 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int file_des)
{
	static char	*buff[MAX_FILE_DES];
	char		*ln_break;
	char		*line;

	if (file_des < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[file_des] = read_and_concat_buff(file_des, buff[file_des]);
	ln_break = ft_gnl_strchr(buff[file_des], '\n');
	line = ft_gnl_substr(buff[file_des], ln_break);
	buff[file_des] = realloc_buff(buff[file_des], ln_break);
	return (line);
}

char	*read_and_concat_buff(int file_des, char *buff)
{
	int		bytes_read;
	char	*read_buff;

	bytes_read = 1;
	read_buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!read_buff)
		return (NULL);
	while (bytes_read && !ft_gnl_strchr(buff, '\n'))
	{
		bytes_read = read(file_des, read_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buff);
			return (NULL);
		}
		read_buff[bytes_read] = '\0';
		buff = ft_gnl_strjoin(buff, read_buff);
	}
	free(read_buff);
	return (buff);
}

char	*realloc_buff(char *buff, char *ln_break)
{
	char	*new_buff;
	int		copy_size;

	if (!ln_break)
	{
		free(buff);
		return (NULL);
	}
	copy_size = ft_gnl_strlen(ln_break) - 1;
	new_buff = (char *) malloc(copy_size + 1);
	if (!new_buff)
		return (NULL);
	ft_gnl_strlcpy(new_buff, ln_break + 1, copy_size + 1);
	free(buff);
	return (new_buff);
}
