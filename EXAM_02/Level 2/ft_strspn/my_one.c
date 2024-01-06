#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;

	while (s[i])
	{
		if (ft_strchr(accept, s[i]) == 0)
			break;
		++i;
	}
	return (i);
}

int		main(void)
{
	printf("%ld\t   VS\t  %ld\n", ft_strspn("Hello", "H"), strspn("Hello", "H"));
	printf("%ld\t   VS\t  %ld\n", ft_strspn("Hello", "l"), strspn("Hello", "l"));
	printf("%ld\t   VS\t  %ld\n", ft_strspn("Hellllo", "Hel"), strspn("Hellllo", "Hel"));
	printf("%ld\t   VS\t  %ld\n", ft_strspn("Helo", "Hell"), strspn("Helo", "Hell"));
	return (0);
}
