/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:30:27 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/25 18:58:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_raw_line(int fd, char *raw_line)
{
	char	*block_of_chars;
	int		fd_readed_chars;

	if (!raw_line)
		raw_line = ft_calloc(1, 1);
	block_of_chars = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	fd_readed_chars = 1;
	while (fd_readed_chars > 0)
	{
		fd_readed_chars = read(fd, block_of_chars, BUFFER_SIZE);
		if (fd_readed_chars == -1)
		{
			free(raw_line);
			free(block_of_chars);
			return (NULL);
		}
		block_of_chars[fd_readed_chars] = '\0';
		raw_line = ft_join_and_free(raw_line, block_of_chars);
		if (ft_strchr(block_of_chars, '\n'))
			break ;
	}
	free(block_of_chars);
	return (raw_line);
}

char	*ft_cleaned_line(char *raw_line)
{
	char	*cleaned_line;
	int		i;

	i = 0;
	if (!raw_line[i])
		return (NULL);
	while (raw_line[i] && raw_line[i] != '\n')
		i++;
	cleaned_line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
	{
		cleaned_line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
		cleaned_line[i] = '\n';
	return (cleaned_line);
}

char	*ft_next_line(char *buff)
{
	char	*next_buff;
	int		i;
	int		j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
	{
		free(buff);
		return (NULL);
	}
	next_buff = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buff[i])
		next_buff[j++] = buff[i++];
	free(buff);
	return (next_buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*one_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_raw_line(fd, buff);
	if (!buff)
		return (NULL);
	one_line = ft_cleaned_line(buff);
	buff = ft_next_line(buff);
	return (one_line);
}

// int	main(void)
// {
// 	char	**list_of_lines = (void *)malloc(sizeof(char *) * BUFFER_SIZE);
// 	int		fd;
// 	int		i = 0;

// 	fd = open("pokus.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
		
// 	while (i < 10)
// 	{
// 		list_of_lines[i] = get_next_line(fd);
// 		printf("%s", list_of_lines[i]);
// 		free(list_of_lines[i++]);
// 	}

// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	free (list_of_lines);
// 	close(fd);
// 	return (0);
// }
