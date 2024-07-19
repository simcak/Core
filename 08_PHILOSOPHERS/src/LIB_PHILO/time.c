/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:07:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/19 17:55:10 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * this function returns the current time in miliseconds or microseconds
 */
long	get_precise_time(int type)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (printf(R"Error: gettimeofday() failed\n"RST), ERROR);
	if (type == MILISEC)
		return ((time.tv_sec * (long)1e3) + (time.tv_usec / 1e3));
	if (type == MICROSEC)
		return ((time.tv_sec * (long)1e6) + time.tv_usec);
	return (ERROR);
}

/**
 * This function sleeps for a given time in microseconds [us]
 * 1) is the dinner over?
 * 2) usleep if remaining time is more than 1ms
 * 3) spinlock if remaining time is less than 1ms
 * @param sleep_time time to sleep in microseconds [us]
 */
void	ft_usleep(long sleep_time, t_dinner *dinner)
{
	long	start_time;
	long	rem;

	// sleep_time *= 1e3;
	start_time = get_precise_time(MICROSEC);
	while (get_precise_time(MICROSEC) - start_time < sleep_time)
	{
		if (dinner_finished(dinner))
			return ;
		rem = sleep_time - (get_precise_time(MICROSEC) - start_time);
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while(get_precise_time(MICROSEC) - start_time < sleep_time)
				;
	}
}
