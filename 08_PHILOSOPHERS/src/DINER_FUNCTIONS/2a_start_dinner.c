/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2a_start_dinner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:11:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 23:19:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Routine for dining - eat, sleep, think
 * 1) While the dinner is not finished (all philos are't full or dead)
 *    - Philo is full only if we have meal_limit on input and we reached it
 *    - Philo is dead if the last meal time is > time_to_die
 * 2) Philo eats, sleeps and thinks in a loop
 */
static void	routine(t_philos *philo, t_dinner *dinner)
{
	while (!dinner_finished(dinner))
	{
		philo_eat(philo);
		write_status(philo, SLEEP);
		ft_usleep(dinner->time_to_sleep, dinner);
		philo_think(philo);
	}
}

/**
 * Philosopher's dining routine (one philo)
 * 1) Wait for the philo thread, monitor thread and time set before dining
 * 2) Set the last meal time (beginning of the dinner)
 * 3) Increase the num of dining philos for monitor thread (same as in dining)
 * 4) Write the status and wait for the dinner to finish
 */
static void	*lonely_philo(void *data)
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
 * Philosopher's dining routine (more than one philo)
 * 1) Wait for all philos to start dining
 * 2) Set the last meal time (beginning of the dinner)
 * 3) Increase the num of dining philos for monitor thread (for
 * 	  all_philos_dining func) - only if all philos are created than are all
 * 	  dining, than they are all ready
 * 4) Pre routine crossroad - force the odd or even philos think (and let the
 * 	  others eat) in the first round.
 * 5) Run the routine - eat, sleep, think
 */
static void	*dining(void *data)
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
	pre_routine_crossroad(philo);
	routine(philo, dinner);
	return (NULL);
}

/**
 * This is the function running by monitor thread.
 * First it waits - spinlock - for all philos to start dining.
 * Than the monitor thread runs while the dinner is not finished.
 * It checks if all philos are full or if any of them died.
 * Based on that we set or write.
 * We affect other threads by setting the finish_dinner bool.
 */
static void	*monitor_dinner(void *data)
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
 * We handle the cases:
 * 		- meal_limit == 0 
 * 		- num_of_philos == 1
 * 		- num_of_philos > 1
 * For each philo we create a thread than we wait for all philo thread to be
 * created. Then we create a monitor thread, set the start time and wait for
 * all philos with join.  
 */
int	start_dinner(t_dinner *dinner)
{
	int			i;
	t_philos	*philos;

	i = -1;
	philos = dinner->philos;
	if (dinner->meal_limit == 0)
		return (SUCCESS);
	else if (dinner->num_of_philos == 1)
		safe_thread(&philos[0].thread_id, CREATE, lonely_philo, &philos[0]);
	else
		while (++i < dinner->num_of_philos)
			safe_thread(&philos[i].thread_id, CREATE, dining, &philos[i]);
	safe_thread(&dinner->monitor, CREATE, monitor_dinner, dinner);
	dinner->start_time = get_precise_time(MILISEC);
	set_bool(&dinner->dinner_mutex, &dinner->all_philos_ready, true);
	i = -1;
	while (++i < dinner->num_of_philos)
		safe_thread(&philos[i].thread_id, JOIN, NULL, NULL);
	set_bool(&dinner->dinner_mutex, &dinner->finish_dinner, true);
	safe_thread(&dinner->monitor, JOIN, NULL, NULL);
	return (SUCCESS);
}
