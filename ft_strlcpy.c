/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:00:58 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/18 18:46:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	
	len = 0;
	if (!src)
        return (0);
	while (src[len] && len < (size - 1))
	{
		dst[len] = src[len];
		len++;
	}
	if (size > 0)
        dst[len] = '\0';
	while (src[len])
		len++;
	return (len);
}
