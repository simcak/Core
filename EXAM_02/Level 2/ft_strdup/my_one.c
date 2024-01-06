#include <string.h>	//strdup
#include <stdlib.h>	//maloc
#include <stdio.h>	//printf

char    *ft_strdup(char *src)
{
	char	*duplicated;
	int		length = 0;
	int		i = 0;

	while (src[length])
		length++;
	duplicated = malloc(sizeof(duplicated) * (length + 1));
	if (!duplicated)
		return (duplicated);
	while (src[i])
	{
		duplicated[i] = src[i];
		i++;
	}
	duplicated[i] = '\0';
	return (duplicated);
}

int	main(void)
{
	printf("%s\t\t   VS\t    %s\n", ft_strdup("42"), strdup("42"));
	printf("%s\t   VS\t    %s\n", ft_strdup("Hello world!"), strdup("Hello world!"));
	return (0);
}