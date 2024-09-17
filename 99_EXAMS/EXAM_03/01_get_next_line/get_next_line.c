#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*str_buf;
	int		i = 0;
	int		byte;
	char	c;

	if (fd < 0 || BUFFER_SIZE < 1)						// Check if the file descriptor is valid
		return (NULL);

	str_buf = (char *)malloc(42000000);					// Allocate memory for the buffer
	byte = read(fd, &c, 1);								// Read the first byte from the file descriptor

	while (byte > 0)									// While the read was successful
	{
		str_buf[i++] = c;								// Store the byte in the return string buffer
		if (c == EOF || c == '\n')						// If the byte is the end of file or a newline character
			break ;										// Break the loop
		byte = read(fd, &c, 1);							// Read the next byte
	}

	if (i == 0 || byte < 0)								// Check if there is something in the file || the read was successful
	{
		free(str_buf);									// Free the allocated memory if not
		return (NULL);									// And return NULL
	}
	str_buf[i] = '\0';									// It must be null-terminated
	return (str_buf);									// Return the string buffer
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
