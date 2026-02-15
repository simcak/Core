/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:07:23 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/24 21:22:13 by psimcak          ###   ########.fr       */
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
		return (printf("%sError: gettimeofday() failed%s\n", R, RST), ERROR);
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
	long	time;
	long	rem;

	time = get_precise_time(MICROSEC);
	while (get_precise_time(MICROSEC) - time < sleep_time)
	{
		if (dinner_finished(dinner))
			return ;
		rem = sleep_time - (get_precise_time(MICROSEC) - time);
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_precise_time(MICROSEC) - time < sleep_time)
				;
	}
}
