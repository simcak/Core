/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:41:20 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/21 15:05:06 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
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

char    **ft_split(char const *s, char c)
{
	char	**str;
	int		words;
	char	*start;
	int		i;

	words = ft_count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		str[i] = (char *)malloc(s - start + 1);
		if (!str[i])
			return (0);
		ft_strncpy(str[i], start, s - start);
		str[i][s - start] = 0;
		i++;
	}
	str[i] = 0;
	return (str);
}
