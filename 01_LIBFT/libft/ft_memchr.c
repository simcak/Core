/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:14:19 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/24 17:25:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (i < n)
	{
		if (*(char *)(s + i) == (char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
