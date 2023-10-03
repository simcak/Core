/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:41:20 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/03 16:40:48 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	ft_count_parts(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (src[i])
			dest[i] = src[i];
		else
			dest[i] = 0;
		i++;
	}
	return (dest);
}
// dest[i] = 0; must be in (i < n) or buffer owerflow

char	**ft_split(char const *str2split, char char4split)
{
	char	**str;
	int		parts;
	char	*start;
	int		i;

	parts = ft_count_parts(str2split, char4split);
	str = (char **)malloc(sizeof(char *) * (parts + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < parts)
	{
		while (*str2split == char4split)
			str2split++;
		start = (char *)str2split;
		while (*str2split && *str2split != char4split)
			str2split++;
		str[i] = (char *)malloc(str2split - start + 1);
		if (!str[i])
			return (0);
		ft_strncpy(str[i], start, str2split - start);
		str[i++][str2split - start] = 0;
	}
	str[i] = 0;
	return (str);
}
