#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
        	str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
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