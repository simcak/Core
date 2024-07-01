/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:39:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/01 20:46:27 by psimcak          ###   ########.fr       */
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
	return (get_bool(dinner->dinner_mutex, &dinner->finish_dinner));
}

/**
 * This function waits for all philosophers/threads to be ready
 * Spinlock till all philosophers are ready
 */
void	wait_before_start(t_dinner *dinner)
{
	while (get_bool(dinner->dinner_mutex, &dinner->all_philos_ready) == false)
		;
}
