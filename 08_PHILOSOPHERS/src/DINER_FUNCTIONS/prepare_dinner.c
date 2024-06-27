/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/27 16:54:26 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

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
	dinner->forks = malloc(sizeof(t_fork) * dinner->num_of_philos);
	dinner->philos = malloc(sizeof(t_philos) * dinner->num_of_philos);
	if (!dinner->forks || !dinner->philos)
		return(printf("%sError: malloc failed%s\n", R, RST));
	// dinner->start_dinner ; // TODO
	dinner->end_dinner = false;
	return (SUCCESS);
}
