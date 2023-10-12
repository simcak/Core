/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:07:52 by lwoiton           #+#    #+#             */
/*   Updated: 2023/07/07 22:58:45 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*s_joined;

	if (!s1)
	{
		s1 = (char *) malloc (1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_gnl_strlen(s1);
	s2_len = ft_gnl_strlen(s2);
	s_joined = (char *) malloc(s1_len + s2_len + 1);
	if (!s_joined)
		return (NULL);
	while (s1 && *s1)
		*s_joined++ = *s1++;
	while (*s2)
		*s_joined++ = *s2++;
	*s_joined = '\0';
	free(s1 - s1_len);
	return (s_joined - s1_len - s2_len);
}

char	*ft_gnl_substr(char *s, char *ln_break)
{
	char	*ss;
	int		len;

	if (!s || !*s)
		return (NULL);
	if (!ln_break)
		ln_break = ft_gnl_strchr(s, '\0') - 1;
	len = (ln_break - s) + 1;
	ss = (char *) malloc(len + 1);
	if (!ss)
		return (NULL);
	ft_gnl_strlcpy(ss, s, len + 1);
	return (ss);
}

//Added the preliminary check for validity on s
char	*ft_gnl_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char) c)
			return (s);
		s++;
	}
	if (*s == (unsigned char) c)
		return (s);
	return (NULL);
}

//Added the preliminary check for validity on c
size_t	ft_gnl_strlen(char const *c)
{
	size_t	len;

	if (!c)
		return (0);
	len = 0;
	while (c[len])
		len++;
	return (len);
}

size_t	ft_gnl_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (ft_gnl_strlen(src));
}
