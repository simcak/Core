#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 2, 1, 7};
	int size_len = sizeof(arr) / sizeof(int);
	int start, end, sum, i;
	int fd[2];

	if (pipe(fd) == -1)
		return 0;
	
	int id = fork();
	if (id == -1)
		return 0;
	
	if (id == 0) {
		start = 0;
		end = size_len / 2;
	}
	else {
		start = size_len / 2;
		end = size_len;
	}
	sum = 0;
	i = start;
	while (i < end)
		sum += arr[i++];
	printf("suma je: %d \n", sum);

	if (id == 0) {
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else {
		int sum_from_child;
		close(fd[1]);
		read(fd[0], &sum_from_child, sizeof(sum_from_child));
		close(fd[0]);
		sum += sum_from_child;
		wait(NULL);
		printf("Total sum is: %i \n", sum);
	}

	return 0;
}