/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_start_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:11:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/02 14:26:32 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

static int	philo_think(t_philos *philo)
{
	write_status(philo, THINK, DEBUG);
	return (SUCCESS);
}

static int	philo_eat(t_philos *philo)
{
	uint64_t	time;

	if (safe_mutex(&philo->r_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_RF, DEBUG);
	if (safe_mutex(&philo->l_fork->fork_mutex, LOCK))
		return (FAILURE);
	write_status(philo, TAKE_LF, DEBUG);

	time = get_precize_time(MILISEC);
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

void	*dining(void *data)
{
	t_philos	*philo;
	t_dinner	*dinner;

	philo = (t_philos *)data;
	dinner = philo->dinner;
	while (get_precize_time(MILISEC) < (uint64_t)dinner->start_time)
		;
	while (!dinner_finished(dinner))
	{
		if (philo_eat(philo))
			return (NULL);
		write_status(philo, SLEEP, DEBUG);
		ft_usleep(dinner->time_to_sleep, dinner);
		if (philo_think(philo))	// TODO
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
	dinner->start_time = get_precize_time(MILISEC) + 40;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, CREATE, dining, &dinner->philos[i]))
			return (FAILURE);
	i = -1;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, JOIN, NULL, NULL))
			return (FAILURE);
	return (SUCCESS);
}
