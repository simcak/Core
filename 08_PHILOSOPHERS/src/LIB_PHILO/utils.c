/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:39:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/02 14:09:03 by psimcak          ###   ########.fr       */
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
 * Returns the length of the string
*/
int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

/**
 * Predicate function to check if dinner is finished
 */
bool	dinner_finished(t_dinner *dinner)
{
	return (get_bool(&dinner->dinner_mutex, &dinner->finish_dinner));
}
