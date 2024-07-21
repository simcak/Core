/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:33:17 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/21 23:57:12 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 *
 */
int	philo_think(t_philos *philo)
{
	write_status(philo, THINK);
	return (SUCCESS);
}

/**
 *
 */
int	philo_eat(t_philos *philo)
{
	long		time;
	t_dinner	*dinner;

	dinner = philo->dinner;
	if (safe_mutex(&philo->r_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_RF);
	if (safe_mutex(&philo->l_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_LF);

	time = get_precise_time(MILISEC);
	if (time == ERROR)
		return (FAILURE);
	set_long(&philo->philo_mutex, &philo->last_meal_time_ms, time);
	write_status(philo, EAT);
	ft_usleep(philo->dinner->time_to_eat, philo->dinner);
	if (dinner->meal_limit > 0 && philo->meals_counter == dinner->meal_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);

	if (safe_mutex(&philo->r_fork->fork_mutex, UNLOCK))
		return (FAILURE);
	if (safe_mutex(&philo->l_fork->fork_mutex, UNLOCK))
		return (FAILURE);
	return (SUCCESS);
}

/**
 *
 */
bool	philo_died(t_philos *philo)
{
	long		time;
	long		last_meal_time;
	long		time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);

	time = get_precise_time(MILISEC);
	if (time == ERROR)
		return (false);

	time_to_die = philo->dinner->time_to_die / 1e3;
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time_ms);
	if (time - last_meal_time > time_to_die)
		return (true);
	return (false);
}
