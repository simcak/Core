/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:42 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/19 19:54:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Set global rules structure from command line arguments
 */
void	set_global_rules(t_global_rules *g_rules, char **argv)
{
	g_rules->number_of_philosophers = ft_atoi(argv[1]);
	g_rules->time_to_die = ft_atoi(argv[2]);
	g_rules->time_to_eat = ft_atoi(argv[3]);
	g_rules->time_to_sleep = ft_atoi(argv[4]);
}
