#include <stdio.h>
#include <string.h>

char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	
	if (!s1 || !s2)
	{
		return (0);
	}
	while(*s1)
	{
		i = 0;
	   	while(s2[i])
		{
			if(*s1 == s2[i])
				return (char *) s1;
			i++;
		}
		s1++;	
	}
	return (0);
}

int	main(void)
{
	printf("%s\t   VS\t    %s\n", ft_strpbrk("42", "21"), strpbrk("42", "21"));
	printf("%s\t   VS\t    %s\n", ft_strpbrk("42", "7"), strpbrk("42", "7"));
	printf("%s\t   VS\t    %s\n", ft_strpbrk("Hello w", "wo"), strpbrk("Hello w", "wo"));
	return (0);
}