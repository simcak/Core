#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_read;
	static int 	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	for (int i = 0; i < 16; i++) {
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
