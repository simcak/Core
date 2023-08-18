/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:22:59 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/18 16:02:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	allocMemSize;
	void	*ptr;

	if (nmemb && ((size_t)(-1) / nmemb) < size)
		return (0);
	allocMemSize = nmemb * size;
	ptr = (void *)malloc(allocMemSize);
	if (!ptr)
		return (0);
	ft_bzero(ptr, allocMemSize);
	return (ptr);
}
