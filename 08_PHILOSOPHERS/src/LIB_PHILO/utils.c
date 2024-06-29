/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:39:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 16:39:39 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Check if philosopher id is even or odd
 */
int	philo_id_is(t_philos *philo)
{
	if (philo->id % 2 == 0)
		return (EVEN);
	if (philo->id % 2 == 1)
		return (ODD);
	return (FAILURE);
}

/**
 * @brief Returns the length of the string
*/
int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}
