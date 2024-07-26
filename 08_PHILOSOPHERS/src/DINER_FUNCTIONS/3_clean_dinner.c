/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_clean_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 02:14:36 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 19:28:04 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Destroy mutex and free memory
 * After the dinner is over, we "clean the table".
 */
void	clean_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->num_of_philos)
	{
		safe_mutex(&dinner->philos[i].philo_mutex, DESTROY);
		safe_mutex(&dinner->forks[i].fork_mutex, DESTROY);
	}
	safe_mutex(&dinner->dinner_mutex, DESTROY);
	safe_mutex(&dinner->print_mutex, DESTROY);
	free(dinner->philos);
	free(dinner->forks);
}
