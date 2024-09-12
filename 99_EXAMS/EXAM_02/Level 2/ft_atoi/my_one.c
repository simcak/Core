#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	i = 0;
	int	sign = 1;
	int	result = 0;

	while(str[i] >= 1 && str[i] <= 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+')
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while(str[i] >= '0' && str[i] <= '9')
		result = ((result * 10) + str[i++] - '0');
	return (result * sign);
}

int	main()
{
	printf("%d\t   VS    %d\n", ft_atoi("-42"), atoi("-42"));
	printf("%d\t   VS    %d\n", ft_atoi("-0242"), atoi("-0242"));
	printf("%d\t   VS    %d\n", ft_atoi("+42"), atoi("+42"));
	printf("%d\t   VS    %d\n", ft_atoi("+-42"), atoi("+-42"));
	printf("%d\t   VS    %d\n", ft_atoi("- 42"), atoi("- 42"));
	printf("%d\t   VS    %d\n", ft_atoi("a42"), atoi("a42"));
	printf("%d\t   VS    %d\n", ft_atoi("   -42"), atoi("   -42"));
	printf("%d\t   VS    %d\n", ft_atoi("*42"), atoi("*42"));
}