/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:59:47 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/29 18:38:42 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	if ((!dst || !src) && !size)
		return (0);
	dest_len = ft_strlen(dst);
	j = dest_len;
	i = 0;
	if (dest_len <= (size - 1) && size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dest_len > size)
		dest_len = size;
	return (dest_len + ft_strlen(src));
}
