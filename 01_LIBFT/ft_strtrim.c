/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:50:46 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/21 14:13:03 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(size_t	i, char c, char const *set)
{
	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_char_in_set(i, s1[start], set))
		start++;
	while ((end > start) && ft_char_in_set(i, s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
