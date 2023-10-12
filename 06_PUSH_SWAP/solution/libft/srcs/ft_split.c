/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:23:31 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/18 00:06:12 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cnt_substr(char const *s, char del)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (*s == del)
			s++;
		while (*s && *s != del)
		{
			s++;
			if (!*s || *s == del)
				count++;
		}
	}
	return (count);
}

int	ft_sep_strs(char const *s, char c, char **str_arr_iter)
{
	char	*start;

	while (*s)
	{
		while (*s == c)
			s++;
		start = (char *) s;
		while (*s && *s != c)
			s++;
		if (*s == c || s > start)
		{
			*str_arr_iter = ft_substr(start, 0, s - start);
			if (!str_arr_iter)
			{
				free(str_arr_iter);
				return (0);
			}
			start = (char *) s;
			str_arr_iter++;
		}
	}
	*str_arr_iter = (void *) 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**str_arr;
	char		**str_arr_iter;

	if (!s)
		return (NULL);
	str_arr = (char **) malloc((ft_cnt_substr(s, c) + 1) * sizeof(char *));
	if (!str_arr)
	{
		free(str_arr);
		return (NULL);
	}
	str_arr_iter = str_arr;
	if (!ft_sep_strs(s, c, str_arr_iter))
		return (NULL);
	return (str_arr);
}
