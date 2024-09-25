#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i = -1;

	while (src[++i]);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return dest;
}

char	*get_next_line(int fd)
{
	char		line_out[70000];
	static char	buffer_line[BUFFER_SIZE];
	static int	buffer_read;
	static int 	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer_line, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line_out[i++] = buffer_line[buffer_pos++];
		if (line_out[i - 1] == '\n')
			break ;
	}
	line_out[i] = '\0';
	if (i == 0)
		return NULL;
	return ft_strdup(line_out);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd))) {
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
