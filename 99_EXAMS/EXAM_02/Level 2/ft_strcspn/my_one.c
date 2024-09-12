#include <string.h>
#include <stdio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i = 0;
	int	j = 0;

	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	main(void)
{
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("42", "-"), strcspn("42", "-"));
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("42", "4"), strcspn("42", "4"));
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("42", "-4"), strcspn("42", "-4"));
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("-42", "4"), strcspn("-42", "4"));
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("-42", "+4"), strcspn("-42", "+4"));
	printf("%ld\t   VS\t    %ld\n", ft_strcspn("42   7", "7"), strcspn("42   7", "7"));
	return (0);
}