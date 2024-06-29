/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 12:18:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Just check if the arguments are valid or not
 */
static int	args_are_invalid(t_dinner *dinner)
{
	int	err;

	err = 0;
	if (dinner->num_of_philos >= 200 || dinner->num_of_philos <= 0)
		err = printf("%sError: ok is 0 <= num_of_philos <= 200 %s\n", R, RST);
	if (dinner->time_to_die <= 60 * 1e3)
		err = printf("%sError: time to die must be >= 60ms%s\n", R, RST);
	if (dinner->time_to_eat <= 60 * 1e3)
		err = printf("%sError: time to eat must be >= 60ms%s\n", R, RST);
	if (dinner->time_to_sleep <= 60 * 1e3)
		err = printf("%sError: time to sleep must be >= 60ms%s\n", R, RST);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * Initialize forks
 */
static int	forks_init(t_dinner *dinner)
{
	int	i;

	dinner->forks = malloc(sizeof(t_fork) * dinner->num_of_philos);
	if (!dinner->forks)
		return (printf("%sError: malloc failed%s\n", R, RST));
	i = -1;
	while (++i < dinner->num_of_philos)
	{
		dinner->forks[i].id = i;
		if (safe_mutex(&dinner->forks[i].fork_mutex, INIT))
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * Assign forks to philosophers
 * right 🍽 fork is on same position as philosopher
 * left  🍽 fork is on position (philosopher + 1) % num_of_philos
 * [1] - [2] - [3] - [4] - [5]		// 🤔🤔🤔🤔🤔
 * |  \  |  \  |  \  |  \	|  \    // assigning forks
 * 0     1     2     3     4     0	// 🍽🍽🍽🍽🍽
 */
static void	assign_forks(t_dinner *dinner, t_philos *philo)
{
	long	f_id;
	long	p_id;

	f_id = philo->id - 1;
	p_id = philo->id;
	philo->r_fork = &dinner->forks[f_id].fork_mutex;
	philo->l_fork = &dinner->forks[(p_id) % dinner->num_of_philos].fork_mutex;
}

/**
 * Initialize philosophers
 */
static int	philos_init(t_dinner *dinner)
{
	int			i;
	t_philos	*philo;

	dinner->philos = malloc(sizeof(t_philos) * dinner->num_of_philos);
	if (!dinner->philos)
		return (printf("%sError: malloc failed%s\n", R, RST));
	i = -1;
	while (++i < dinner->num_of_philos)
	{
		philo = &dinner->philos[i];
		philo->id = i + 1;
		philo->meals_counter = 0;
		assign_forks(dinner, philo);
	}
	return (SUCCESS);
}

/**
 * Set global rules structure from command line arguments
 * time is stored in microseconds BUT on input we have miliseconds.
 */
int	prepare_dinner(t_dinner *dinner, char **argv)
{
	dinner->num_of_philos = ft_atol(argv[1]);
	dinner->time_to_die = ft_atol(argv[2]) * 1e3;
	dinner->time_to_eat = ft_atol(argv[3]) * 1e3;
	dinner->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (args_are_invalid(dinner))
		return (FAILURE);
	if (forks_init(dinner))
		return (FAILURE);
	if (philos_init(dinner))
		return (FAILURE);
	// dinner->start_dinner ; // TODO
	dinner->end_dinner = false;
	return (SUCCESS);
}
