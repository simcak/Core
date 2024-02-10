/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:32:05 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/24 17:26:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	i = ft_cstrlen(s);
	c2 = (unsigned char)c;
	if (!c2)
		return (&((char *)s)[i]);
	while (i >= 0)
	{
		if (s[i] == c2)
			return (&((char *)s)[i]);
		i--;
	}
	return (0);
}
