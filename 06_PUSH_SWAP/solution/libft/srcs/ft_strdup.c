/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:44:07 by lwoiton           #+#    #+#             */
/*   Updated: 2023/02/04 13:21:01 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*d_s;

	size = ft_strlen((char *) s) + 1;
	d_s = (char *) malloc(size);
	if (!d_s)
		return (NULL);
	d_s = (char *) ft_memcpy((void *) d_s, (const void *) s, size);
	return (d_s);
}
