#include <unistd.h>

void	last_word(char *str)
{
	int	i = 0;
	int	start = 0;

	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && 
			(str[i+1] >= '!' && str[i+1] <= 126))
			start = i + 1;
		i++;
	}
	while (str[start])
	{
		if (str[start] == ' ' || str[start] == '\t')
			break;
		write (1, &str[start++], 1);
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		last_word(av[1]);
	write (1, "\n", 1);
	return (0);
}