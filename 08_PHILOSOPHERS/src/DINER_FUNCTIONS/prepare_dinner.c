/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/28 20:56:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Check if arguments are valid
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
 * Initialize philosophers
 */
static int	philos_init(t_dinner *dinner)
{
	dinner->philos = malloc(sizeof(t_philos) * dinner->num_of_philos);
	if (!dinner->philos)
		return (printf("%sError: malloc failed%s\n", R, RST));
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
