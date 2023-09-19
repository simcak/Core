/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:30:27 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/19 18:48:32 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_cleaned_line(char *raw_line)
{
	char	*one_line;
	int		i;

	if (!raw_line)
		return (NULL);
	i = ft_strlen(ft_strchr(raw_line, '\n'));
	one_line = (void *)malloc((i + 1) * sizeof(char));
	if (!one_line)
		return (NULL);
	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
	{
		one_line[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
		one_line[i++] = '\n';
	one_line[i] = '\0';
	return (one_line);
}
// raw_line = there could be zero \n or multiple \n
// one_line = cleaned line ending with \n

char	*ft_trim_buff(char *buff, char *one_line)
{
	char	*trimmed_buff;

	trimmed_buff = ft_strtrim(buff, one_line);
	return (trimmed_buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*temp_line;
	int			fd_read_out;
	char		*new_buff;

	fd_read_out = 1;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_line = (void *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_line)
		return (NULL);
	if (!buff)
		buff = ft_strdup("");
	while (fd_read_out && !(ft_strchr(buff, '\n')))
	{
		fd_read_out = read(fd, temp_line, BUFFER_SIZE);
		if (fd_read_out <= 0)
		{
			free (temp_line);
			return (NULL);
		}
		temp_line[fd_read_out] = '\0';
		new_buff = buff;
		buff = ft_strjoin(new_buff, temp_line);
		free(new_buff);
	}
	free (temp_line);
	temp_line = ft_cleaned_line(buff);
	new_buff = ft_trim_buff(buff, temp_line);
	free (buff);
	buff = new_buff;
	return (temp_line);
}
// fd_read_out = number of bytes readed (the output from read function)

int	main(void)
{
	int		fd;

	fd = open("pokus.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
