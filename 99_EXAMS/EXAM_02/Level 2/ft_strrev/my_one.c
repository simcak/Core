#include <stdio.h>

char	*ft_strrev(char *str)
{
	int		length = 0;
	int		i = 0;
	int		temp;

	while (str[length])
		length++;
	while (i < length / 2)
	{
		temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
		i++;
	}
	return (str);
}

int main(void)
{
    char str[] = "42Prague Hello!!";
    printf("%s\n", ft_strrev(str));
	return (0);
}
