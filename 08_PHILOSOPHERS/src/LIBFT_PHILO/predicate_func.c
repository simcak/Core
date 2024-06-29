/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 13:46:40 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 13:59:57 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	philo_id_is_even(t_philos *philo)
{
	return (philo->id % 2 == 0);
}

int	philo_id_is_odd(t_philos *philo)
{
	return (philo->id % 2 != 0);
}