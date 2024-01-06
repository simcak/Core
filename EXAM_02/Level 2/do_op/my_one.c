#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int	num_1;
	int	num_2;

	if (ac == 4)
	{
		num_1 = atoi(av[1]);
		num_2 = atoi(av[3]);
		if (av[2][0] == '+')
			printf("%d", num_1 + num_2);
		if (av[2][0] == '-')
			printf("%d", num_1 - num_2);
		if (av[2][0] == '*')
			printf("%d", num_1 * num_2);
		if (av[2][0] == '/')
			printf("%d", num_1 / num_2);
	}
	printf("\n");
	return (0);
}
