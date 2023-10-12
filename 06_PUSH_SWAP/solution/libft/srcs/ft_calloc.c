/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:19:31 by lwoiton           #+#    #+#             */
/*   Updated: 2023/03/03 15:38:05 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*nptr;
	size_t	size_max;

	size_max = nmemb * size;
	if (!nmemb || !size)
	{
		nptr = malloc(0);
		return (nptr);
	}
	if (nmemb != size_max / size)
		return (NULL);
	nptr = (void *) malloc(nmemb * size);
	if (!nptr)
		return (NULL);
	ft_bzero(nptr, nmemb * size);
	return (nptr);
}
