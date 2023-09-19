/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:31:11 by psimcak           #+#    #+#             */
/*   Updated: 2023/09/19 18:36:49 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*joined;
	size_t	s;
	size_t	j;

	s = 0;
	j = 0;
	joined = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!joined)
		return (NULL);
	while (str1 && str1[s])
		joined[j++] = str1[s++];
	s = 0;
	while (str2 && str2[s])
		joined[j++] = str2[s++];
	joined[j] = '\0';
	return (joined);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int character)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)character)
			return ((char *)(str + i));
		i++;
	}
	if (!character)
		return (&((char *)str)[i]);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	str = (void *)malloc((ft_strlen(s1) - ft_strlen(set) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = ft_strlen(set);
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	int		i;

	len = ft_strlen((char *)s) + 1;
	dup = (char *)malloc(len);
	if (!dup)
		return (0);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
