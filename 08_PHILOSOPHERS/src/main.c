/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:52:35 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/26 19:07:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/** 
 * 1) Initialize argv && the list of all philosophers = prepare dinner
 * 2) Accual philo program = start dinner
 */
int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (argc == 5 || argc == 6)
	{
		if (prepare_dinner(&dinner, argv))
			return (FAILURE);
		if (start_dinner(&dinner))
			return (FAILURE);
		clean_dinner(&dinner);
	}
	else
		return (printf("%sError: wrong number of arguments%s\n", R, RST));
	return (SUCCESS);
}
