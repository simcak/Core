#include <unistd.h>

int	repete(char *str, char c, int i)
{
	int	j = 0;

	while (j < i)
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

void	inter(char *first_par, char *second_par)
{
	int	i = 0;
	int	j;

	while (first_par[i])
	{
		j = 0;
		while (second_par[j])
		{
			if ((first_par[i] == second_par[j]) && (repete(first_par, first_par[i], i) == 0))
			{
				write(1, &first_par[i], 1);
				break;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		inter(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}