/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:07:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/02 13:11:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * this function returns the current time in miliseconds or microseconds
 */
uint64_t	get_precize_time(int type)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (printf("%sError: gettimeofday() failed%s\n", R, RST), ERROR);
	if (type == MILISEC)
		return ((time.tv_sec * (uint64_t)1e3) + (time.tv_usec / 1e3));
	if (type == MICROSEC)
		return ((time.tv_sec * (uint64_t)1e6) + time.tv_usec);
	return (ERROR);
}

/**
 * This function sleeps for a given time in microseconds [us]
 * 0) convert input time to microseconds: [ms]->[us]
 * 1) is the dinner over?
 * 2) usleep if remaining time is more than 1ms
 * 3) spinlock if remaining time is less than 1ms
 * @param sleep_time time to sleep in miliseconds [ms]
 */
void	ft_usleep(uint64_t sleep_time, t_dinner *dinner)
{
	uint64_t	start_time;
	uint64_t	rem;

	// sleep_time *= 1e3;
	start_time = get_precize_time(MICROSEC);
	while (get_precize_time(MICROSEC) - start_time < sleep_time)
	{
		if (dinner_finished(dinner))
			return ;
		rem = sleep_time - (get_precize_time(MICROSEC) - start_time);
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while(get_precize_time(MICROSEC) - start_time < sleep_time)
				;
	}
}
