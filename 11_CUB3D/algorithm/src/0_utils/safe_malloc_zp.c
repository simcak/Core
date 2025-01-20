/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc_zp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:54:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/18 11:44:32 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*b_ptr;

	b_ptr = b;
	while (n--)
		*b_ptr++ = (unsigned char)c;
	return (b);
}

static void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

/**
 * If there is an error in malloc, print the error message and exit the program
 * We are allowed to use malloc, perror and exit (also strerror)
 */
void	*ft_smalloc(size_t size, char *msg)
{
	void	*ptr;

	ptr = (void *)ft_calloc(1, size);
	if (!ptr)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
