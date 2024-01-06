#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i = 0;

	while(s1[i] && s2[i])
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	main(void)
{
	printf("%d\t   VS    %d\n", ft_strcmp("42", "42"), strcmp("42", "42"));
	printf("%d\t   VS    %d\n", ft_strcmp("42", "-42"), strcmp("42", "-42"));
	printf("%d\t   VS    %d\n", ft_strcmp("-42", "42"), strcmp("-42", "42"));
	printf("%d\t   VS    %d\n", ft_strcmp("-42", "+42"), strcmp("-42", "+42"));
	return (0);
}