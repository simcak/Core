/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:22:59 by psimcak           #+#    #+#             */
/*   Updated: 2023/08/24 17:18:48 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	alloc_mem_size;
	void	*ptr;

	if (nmemb && ((size_t)(-1) / nmemb) < size)
		return (0);
	alloc_mem_size = nmemb * size;
	ptr = (void *)malloc(alloc_mem_size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, alloc_mem_size);
	return (ptr);
}
