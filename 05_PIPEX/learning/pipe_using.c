#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	child_process(int *fd)
{
	close(fd[0]);
	int x = 42;
	printf("Number to write: %i \n", x);
	if (write(fd[1], &x, sizeof(int)) == -1)
		return 0;
	close(fd[1]);
}

void	parent_process(int *fd)
{
	close(fd[1]);
	int	x_2;
	if (read(fd[0], &x_2, sizeof(int)) == -1)
		return 0;
	x_2 *= 0.5;
	close(fd[0]);
	printf("Number readed: %i \n", x_2);
}

int	main(int argc, char *argv[])
{
	int fd[2];
	//  fd[0] -> read end
	//  fd[1] -> write end

	if (pipe(fd) == -1)
		return 0;

	int id = fork();
	if (id == -1)
		return 0;

	if (id == 0)
		child_process(fd);
	else
		parent_process(fd);

	return 0;
}