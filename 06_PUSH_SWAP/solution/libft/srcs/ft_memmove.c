/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:23:37 by lwoiton           #+#    #+#             */
/*   Updated: 2023/01/20 18:34:10 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*mem_src;
	char		*mem_dest;

	mem_src = (const char *) src;
	mem_dest = (char *) dest;
	if (!mem_dest || !mem_src)
		return (dest);
	if (mem_dest == mem_src)
		return (dest);
	if (mem_dest > mem_src)
	{
		mem_src += n;
		mem_dest += n;
		while (n--)
			*--mem_dest = *--mem_src;
	}
	else
	{
		ft_memcpy(mem_dest, mem_src, n);
	}
	return (dest);
}
