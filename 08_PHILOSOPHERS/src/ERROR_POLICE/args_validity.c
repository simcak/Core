/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:23:20 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 23:24:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Just check if the arguments are valid or not
 */
int	args_are_invalid(t_dinner *dinner, char **argv)
{
	int	err;

	err = 0;
	if (dinner->num_of_philos > 200 || dinner->num_of_philos <= 0)
		err = printf("%sError: ok is 0 < num_of_philos <= 200 %s\n", R, RST);
	if (dinner->time_to_die < 60 * 1e3)
		err = printf("%sError: time to die must be >= 60ms%s\n", R, RST);
	if (dinner->time_to_eat < 60 * 1e3)
		err = printf("%sError: time to eat must be >= 60ms%s\n", R, RST);
	if (dinner->time_to_sleep < 60 * 1e3)
		err = printf("%sError: time to sleep must be >= 60ms%s\n", R, RST);
	if (dinner->meal_limit < 0 && argv[5])
		err = printf("%sError: meal limit must be >= 0%s\n", R, RST);
	if (err)
		return (FAILURE);
	return (SUCCESS);
}
