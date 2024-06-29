/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_start_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:11:05 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 19:19:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

// /**
//  * this function returns the current time in milliseconds [ms]
//  * the return form is: [seconds * 1000 + microseconds / 1000]
//  */
// uint64_t	get_precize_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == ERROR)
// 		return (printf("%sError: gettimeofday() failed%s\n", R, RST), ERROR);
// 	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
// }

void	*dining(void *data)
{
	t_philos	*philo;
	t_dinner	*dinner;

	philo = (t_philos *)data;
	dinner = philo->dinner;
// 	wait_before_start(dinner); // TODO
// 	while (!dinner_finished(dinner))
// 	{
// 		if (philo_eat(philo))	// TODO
// 			return (NULL);
// 		if (philo_sleep(philo))	// TODO
// 			return (NULL);
// 		if (philo_think(philo))	// TODO
// 			return (NULL);
// 	}
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
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, CREATE, dining, &dinner->philos[i]))
			return (FAILURE);
	// all_philos_created(dinner); // TODO
	i = -1;
	while (++i < dinner->num_of_philos)
		if (safe_thread(&dinner->philos[i].thread_id, JOIN, NULL, NULL))
			return (FAILURE);
	return (SUCCESS);
}
