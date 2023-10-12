/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:15:08 by lwoiton           #+#    #+#             */
/*   Updated: 2023/01/21 18:18:07 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*mem_s1;
	unsigned const char	*mem_s2;

	mem_s1 = (const unsigned char *) s1;
	mem_s2 = (const unsigned char *) s2;
	while (n--)
	{
		if (*mem_s1++ != *mem_s2++)
			return ((mem_s1[-1]) - (mem_s2[-1]));
	}
	return (0);
}
