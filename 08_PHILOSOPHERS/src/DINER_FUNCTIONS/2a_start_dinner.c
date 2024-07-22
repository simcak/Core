/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2a_start_dinner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:11:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/22 13:13:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * 
 */
void	*monitor_dinner(void *data)
{
	t_dinner	*dinner;
	int			i;

	dinner = (t_dinner *)data;
	while (!all_philos_dining(dinner, &dinner->dinner_mutex))
		;
	while (!dinner_finished(dinner))
	{
		if (philos_full(dinner))
			set_bool(&dinner->dinner_mutex, &dinner->finish_dinner, true);
		i = -1;
		while (++i < dinner->num_of_philos && !dinner_finished(dinner))
		{
			if (philo_died(&dinner->philos[i]))
			{
				write_status(&dinner->philos[i], DIE);
				set_bool(&dinner->dinner_mutex, &dinner->finish_dinner, true);
			}
		}
	}
	return (NULL);
}

/**
 * 
 */
void	*lonely_philo(void *data)
{
	t_philos	*one_philo;
	t_dinner	*dinner;

	one_philo = (t_philos *)data;
	dinner = one_philo->dinner;
	while (!get_bool(&dinner->dinner_mutex, &dinner->all_philos_ready))
		;
	set_long(&dinner->dinner_mutex, &one_philo->last_meal_time_ms,
		get_precise_time(MILISEC));
	increse_long(&dinner->dinner_mutex, &dinner->num_of_dining_philos);
	write_status(one_philo, TAKE_LF);
	while (!dinner_finished(dinner))
		usleep(200);
	return (NULL);
}

/**
 * Philosopher's dining routine
 */
void	*dining(void *data)
{
	t_philos	*philo;
	t_dinner	*dinner;

	philo = (t_philos *)data;
	dinner = philo->dinner;
	while (!get_bool(&dinner->dinner_mutex, &dinner->all_philos_ready))
		;
	set_long(&dinner->dinner_mutex, &philo->last_meal_time_ms,
		get_precise_time(MILISEC));
	increse_long(&dinner->dinner_mutex, &dinner->num_of_dining_philos);
	if (philo->dinner->num_of_philos % 2 == 0)
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->dinner);
	while (!dinner_finished(dinner))
	{
		if (philo_eat(philo) == FAILURE)
			return (NULL);
		write_status(philo, SLEEP);
		ft_usleep(dinner->time_to_sleep, dinner);
		philo_think(philo, false);
	}
	return (NULL);
}

/**
 * 
 */
int	start_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	if (dinner->meal_limit == 0)
		return (SUCCESS);
	if (dinner->num_of_philos == 1)
		safe_thread(&dinner->philos[0].thread_id, CREATE, lonely_philo,
			&dinner->philos[0]);
	else
		while (++i < dinner->num_of_philos)
			if (safe_thread(&dinner->philos[i].thread_id, CREATE, dining,
					&dinner->philos[i]))
				return (FAILURE);
	safe_thread(&dinner->monitor, CREATE, monitor_dinner, dinner);
	dinner->start_time = get_precise_time(MILISEC);
	set_bool(&dinner->dinner_mutex, &dinner->all_philos_ready, true);
	i = -1;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, JOIN, NULL, NULL))
			return (FAILURE);
	set_bool(&dinner->dinner_mutex, &dinner->finish_dinner, true);
	if (safe_thread(&dinner->monitor, JOIN, NULL, NULL))
		return (FAILURE);
	return (SUCCESS);
}
