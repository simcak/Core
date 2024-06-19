/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:52:35 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/19 19:56:07 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/** 
 * 1) Initialize argv && the list of all philosophers
 */
int	main(int argc, char **argv)
{
	t_global_rules	g_rules;
	t_philosopher	*philo_list;

	if (argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	set_global_rules(&g_rules, argv);
	philo_list = init_list_of_philosophers(g_rules);
	return (0);
}
