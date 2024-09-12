#include <unistd.h>

void	int_to_char(int i)
{
	char	s[10] = "0123456789";

	if (i >= 10)
		int_to_char(i / 10);
	write(1, &s[i % 10], 1);
}

int	main()
{
	int	i = 0;
	while (i <= 100)
	{
		if (i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			int_to_char(i);
		write(1, "\n", 1);
		i++;
	}
}