/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:29 by lwoiton           #+#    #+#             */
/*   Updated: 2023/01/21 18:24:46 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (!*little)
		return ((char *) big);
	while (big[i] && len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] \
		&& len && big[i] == little[0])
		{
			j++;
			len--;
			if (!little[j])
				return ((char *) &big[i]);
		}
		len += (j - 1);
		i++;
	}
	return (NULL);
}
