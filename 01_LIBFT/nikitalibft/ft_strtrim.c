/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:04:40 by nandroso          #+#    #+#             */
/*   Updated: 2023/08/24 18:34:45 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	set_check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		first;
	int		last;
	int		i;

	first = 0;
	i = 0;
	last = ft_strlen(s1);
	while (s1[first] && set_check(s1[first], set))
		first++;
	while (last > first && set_check(s1[last - 1], set))
		last--;
	ptr = (char *)malloc((last - first + 1) * sizeof(char));
	if (!ptr)
	{
		return (NULL);
	}
	while (first < last)
	{
		ptr[i++] = s1[first++];
	}
	ptr[i] = '\0';
	return (ptr);
}
