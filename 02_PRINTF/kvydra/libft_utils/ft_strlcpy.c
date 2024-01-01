/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvydra <kvydra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:53:38 by kvydra            #+#    #+#             */
/*   Updated: 2023/12/30 11:53:51 by kvydra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int	bytes_written;

	bytes_written = ft_strlen((char *)src);
	if (size < 1)
		return (bytes_written);
	while (size > 1 && *src)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (bytes_written);
}
