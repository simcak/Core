/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:29:15 by nandroso          #+#    #+#             */
/*   Updated: 2023/08/17 14:13:04 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;
	unsigned char		*b;

	a = (const unsigned char *)s;
	b = (unsigned char *)&c;
	while (n--)
	{
		if (*a == *b)
		{
			return ((void *)a);
		}
		a++;
	}
	return (NULL);
}
