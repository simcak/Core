/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_start_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:11:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/19 20:58:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 *
 */
static int	philo_think(t_philos *philo)
{
	write_status(philo, THINK, DEBUG);
	return (SUCCESS);
}

/**
 *
 */
static int	philo_eat(t_philos *philo)
{
	long	time;

	if (safe_mutex(&philo->r_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_RF, DEBUG);
	if (safe_mutex(&philo->l_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_LF, DEBUG);

	time = get_precise_time(MILISEC);
	if (time == ERROR)
		return (FAILURE);
	set_long(&philo->philo_mutex, &philo->last_meal_time_ms, time);
	write_status(philo, EAT, DEBUG);
	ft_usleep(philo->dinner->time_to_eat, philo->dinner);

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
		i = -1;
		while (++i < dinner->num_of_philos && !dinner_finished(dinner))
		{
			if (philo_died(&dinner->philos[i]))
			{
				set_bool(&dinner->dinner_mutex, &dinner->finish_dinner, true);
				write_status(&dinner->philos[i], DIE, DEBUG);
			}
		}
	}
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
	while (get_precise_time(MILISEC) < dinner->start_time)
		;
	set_long(&dinner->dinner_mutex, &philo->last_meal_time_ms,
			get_precise_time(MILISEC));
	increse_long(&dinner->dinner_mutex, &dinner->num_of_dining_philos);
	while (!dinner_finished(dinner))
	{
		if (philo_eat(philo) == FAILURE)
			return (NULL);
		write_status(philo, SLEEP, DEBUG);
		ft_usleep(dinner->time_to_sleep, dinner);
		if (philo_think(philo) == FAILURE)	// TODO
			return (NULL);
	}
	return (NULL);
}

/**
 * 
 */
int	start_dinner(t_dinner *dinner)
{
	int	i;

	if (dinner->num_of_philos == 1)
		; // TODO
	i = -1;
	dinner->start_time = get_precise_time(MILISEC) + CHILL_TIME;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, CREATE, dining, &dinner->philos[i]))
			return (FAILURE);
	// safe_thread(&dinner->monitor, CREATE, monitor_dinner, dinner);
	i = -1;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, JOIN, NULL, NULL))
			return (FAILURE);
	return (SUCCESS);
}
