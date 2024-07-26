/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:33:17 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 23:16:39 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Simply write the status and force him to think so other philos can eat.
 * We are forcing him with our usleep function.
 * All other lines of code are just calculation different times.
 * 	- if negativ, then 0
 */
void	philo_think(t_philos *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	write_status(philo, THINK);
	t_eat = philo->dinner->time_to_eat;
	t_sleep = philo->dinner->time_to_sleep;
	t_think = 2 * t_eat - t_sleep;
	if (t_think < 0)
		t_think = 0;
	if (philo->dinner->num_of_philos % 2 != 0)
		ft_usleep(t_think * 0.42, philo->dinner);
}

/**
 * 1) If the number of philosophers is ODD, then the ODD philos think 1st
 * 2) If the number of philosophers is EVEN, then the EVEN philos think 1st
 *
 *  - We use usleep for 30ms so that the desired philos can eat 1st (artificial
 *  delay). This is to prevent the deadlock.
 *  - We simply force the odd or even philos think (and let the others eat) in
 *  the first round.
 */
void	pre_routine_crossroad(t_philos *philo)
{
	if (philo->dinner->num_of_philos % 2 != 0)
	{
		if (philo->id % 2 != 0)
		{
			write_status(philo, THINK);
			ft_usleep(3e4, philo->dinner);
		}
	}
	else if (philo->dinner->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			write_status(philo, THINK);
			ft_usleep(3e4, philo->dinner);
		}
	}
	return ;
}

/**
 * 1) We take the right and left fork = lock them and write the status.
 * 2) We set the last meal time = beginning of the eating + write the eating
 *    status.
 * 3) We sleep for the time_to_eat.
 * 4) We increase the number of meals counter (for the max meals limit).
 * 5) If the meal limit is set and the philo ate enough, we set the full flag.
 * 6) We unlock the right and left fork.
 */
void	philo_eat(t_philos *philo)
{
	long		time;
	t_dinner	*dinner;

	dinner = philo->dinner;
	safe_mutex(&philo->r_fork->fork_mutex, LOCK);
	write_status(philo, TAKE_RF);
	safe_mutex(&philo->l_fork->fork_mutex, LOCK);
	write_status(philo, TAKE_LF);
	time = get_precise_time(MILISEC);
	set_long(&philo->philo_mutex, &philo->last_meal_time_ms, time);
	write_status(philo, EAT);
	ft_usleep(dinner->time_to_eat, dinner);
	increse_long(&philo->philo_mutex, &philo->meals_counter);
	if (dinner->meal_limit > 0 && philo->meals_counter == dinner->meal_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->r_fork->fork_mutex, UNLOCK);
	safe_mutex(&philo->l_fork->fork_mutex, UNLOCK);
}

/**
 * We are answering the question "did the philosopher die?"
 * 1) We get the current time.
 * 2) We convert the time_to_die and time_to_eat to miliseconds.
 * 3) We get the last meal time.
 * 4) If the time from the last meal > time_to_die, we return true.
 * 5) Otherwise, we return false.
 */
bool	philo_died(t_philos *philo)
{
	long		time;
	long		last_meal_time;
	long		time_to_die;

	time = get_precise_time(MILISEC);
	time_to_die = philo->dinner->time_to_die / 1e3;
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time_ms);
	if (time - last_meal_time > time_to_die)
		return (true);
	return (false);
}

/**
 * We are answering the question "are all philosophers full?"
 * read the 'if condition' like:
 * - "If any philosopher DID NOT ate enought -> return false"
 * - We return true only if all philosophers are full.
 */
bool	philos_full(t_dinner *dinner)
{
	int		i;

	i = -1;
	while (++i < dinner->num_of_philos)
	{
		if (!get_bool(&dinner->philos[i].philo_mutex, &dinner->philos[i].full))
			return (false);
	}
	return (true);
}
