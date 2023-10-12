/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:08:27 by lwoiton           #+#    #+#             */
/*   Updated: 2023/01/20 18:34:19 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*mem_src;
	char		*mem_dest;

	mem_src = (char *) src;
	mem_dest = (char *) dest;
	while (n--)
		*mem_dest++ = *mem_src++;
	return (dest);
}
