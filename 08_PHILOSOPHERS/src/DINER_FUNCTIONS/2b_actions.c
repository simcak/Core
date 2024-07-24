/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2b_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:33:17 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/24 21:52:26 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 *
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
	if (philo->dinner->num_of_philos % 2)
		ft_usleep(t_think * 0.42, philo->dinner);
	// else
	// 	if (philo->id % 2 == 0)
	// 		ft_usleep(3e4, philo->dinner);
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
	ft_usleep(dinner->time_to_eat, dinner);
	increse_long(&philo->philo_mutex, &philo->meals_counter);
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
	long		time_to_eat;

	time = get_precise_time(MILISEC);
	if (time == ERROR)
		return (FAILURE);
	time_to_die = philo->dinner->time_to_die / 1e3;
	time_to_eat = philo->dinner->time_to_eat / 1e3;
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time_ms);
	// if (time - last_meal_time > time_to_die)
	if (time - last_meal_time - time_to_eat > time_to_die)
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
