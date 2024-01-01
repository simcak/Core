/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:54:32 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:54:40 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dst_length;
	unsigned int	src_length;
	unsigned int	length;

	dst_length = 0;
	src_length = 0;
	length = 0;
	dst_length = ft_strlen(dest);
	src_length = ft_strlen(src);
	length = dst_length + src_length;
	if (dst_length >= size)
		return (size + src_length);
	if (src_length < size - dst_length)
		ft_memcpy(dest + dst_length, src, src_length + 1);
	else
	{
		ft_memcpy(dest + dst_length, src, size - dst_length - 1);
		*(dest + size - 1) = '\0';
	}
	return (length);
}
