/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:25:13 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/19 18:06:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

// static void	debug_w(t_philos *philo, t_status action, long action_time)
// {
// 	;
// }

void	write_status(t_philos *philo, t_status action, bool debug)
{
	long	action_time;
	long	id;

	safe_mutex(&philo->dinner->print_mutex, LOCK);
	action_time = get_precise_time(MILISEC) - philo->dinner->start_time;
	id = philo->id;
	if (debug)
		;
	// 	debug_w(philo, action, action_time);
	else
	{
		if (dinner_finished(philo->dinner))
			return ;
		if (action == TAKE_LF || action == TAKE_RF)
			printf(W"%-6ld"RST" %ld has taken a fork\n", action_time, id);
		if (action == EAT)
			printf(W"%-6ld"RST" %ld is eating\n", action_time, id);
		if (action == SLEEP)
			printf(W"%-6ld"RST" %ld is sleeping\n", action_time, id);
		if (action == THINK)
			printf(W"%-6ld"RST" %ld is thinking\n", action_time, id);
		if (action == DIE)
			printf(W"%-6ld"RST" %ld died\n", action_time, id);
	}
	safe_mutex(&philo->dinner->print_mutex, UNLOCK);
}
