/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_odd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:46:40 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 14:22:27 by psimcak          ###   ########.fr       */
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
