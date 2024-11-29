/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:54:49 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/29 19:16:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Safe 2D malloc
 */
void	**ft_dalloc(t_main *game, size_t size, int rows, char *msg)
{
	void	**ptr;
	int		i;

	ptr = (void **)malloc(rows * sizeof(void *));
	if (!ptr)
		safe_exit(game, msg);
	i = -1;
	while (++i < rows)
	{
		ptr[i] = (void *)malloc(size);
		if (!ptr[i])
		{
			while (--i >= 0)
				free(ptr[i]);
			free(ptr);
			safe_exit(game, msg);
		}
	}
	return (ptr);
}

/**
 * If there is an error in malloc, print the error message and exit the program
 * We are allowed to use malloc, perror and exit (also strerror)
 */
void	*ft_smalloc(size_t size, char *msg)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
