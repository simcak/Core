#include <unistd.h>

int	repete(char *str, char c, int end)
{
	int	i = 0;

	while (i < end)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return(0);
}

void	ft_union(char *fst_par, char *scnd_par)
{
	int	i = 0;
	int	len = 0;

	while (fst_par[len++])
	while (fst_par[i])
	{
		if (repete(fst_par, fst_par[i], i) == 0)
			write(1, &fst_par[i], 1);
		i++;
	}
	i = 0;
	while (scnd_par[i])
	{
		if ((repete(fst_par, scnd_par[i], len) == 0) && 
			(repete(scnd_par, scnd_par[i], i) == 0))
			write(1, &scnd_par[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_union(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}