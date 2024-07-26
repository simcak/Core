/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:25:13 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 20:37:20 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * 1) we check if the philosophers are full
 * 2) we lock the print mutex
 * 3) we print the action of the philosopher
 * 4) we unlock the print mutex
 */
void	write_status(t_philos *philo, t_status action)
{
	long		action_time;
	long		id;

	if (philos_full(philo->dinner))
		return ;
	safe_mutex(&philo->dinner->print_mutex, LOCK);
	action_time = get_precise_time(MILISEC) - philo->dinner->start_time;
	id = philo->id;
	if ((action == TAKE_LF || action == TAKE_RF)
		&& !dinner_finished(philo->dinner))
		printf(W"%-6ld"RST" %ld has taken a fork\n", action_time, id);
	if (EAT == action && !dinner_finished(philo->dinner))
		printf(W"%-6ld"RST" %ld is eating\n", action_time, id);
	if (SLEEP == action && !dinner_finished(philo->dinner))
		printf(W"%-6ld"RST" %ld is sleeping\n", action_time, id);
	if (THINK == action && !dinner_finished(philo->dinner))
		printf(W"%-6ld"RST" %ld is thinking\n", action_time, id);
	if (DIE == action)
		printf(W"%-6ld"RST" %ld died\n", action_time, id);
	safe_mutex(&philo->dinner->print_mutex, UNLOCK);
}
