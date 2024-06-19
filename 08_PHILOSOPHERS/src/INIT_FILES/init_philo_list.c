/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:36:58 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/19 19:49:42 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

/**
 * Create a new philosopher
 * Mark it by id from 1 to number_of_philosophers
 * Set other parameters from global rules
 */
static t_philosopher	*create_philosopher(int id, t_global_rules rules)
{
	t_philosopher	*new_philosopher;

	new_philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = id;
	new_philosopher->time_to_die = rules.time_to_die;
	new_philosopher->time_to_eat = rules.time_to_eat;
	new_philosopher->time_to_sleep = rules.time_to_sleep;
	new_philosopher->next = NULL;
	return (new_philosopher);
}

/**
 * Add new philosopher to the end of the list
 * If list is empty, add it as the first element
 * If list is not empty, add it as the last element
 * temp is necessary - otherwise we lose the head of the list
 */
static void	add_philosopher(t_philosopher **philo_list,
							t_philosopher *new_philosopher)
{
	t_philosopher	*temp;
	
	if (!philo_list || !new_philosopher)
		return ;
	if (!*philo_list)
		*philo_list = new_philosopher;
	else
	{
		temp = *philo_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_philosopher;
	}
}

/**
 * Initialize the list of all philosophers
 * We create a list of size number_of_philosophers of philosophers
 */
t_philosopher	*init_list_of_philosophers(t_global_rules rules)
{
	t_philosopher	*philo_list;
	t_philosopher	*new_philosopher;
	int				i;

	philo_list = NULL;
	i = -1;
	while (++i < rules.number_of_philosophers)
	{
		new_philosopher = create_philosopher(i + 1, rules);
		if (!new_philosopher)
			return (NULL);
		add_philosopher(&philo_list, new_philosopher);
	}
	return (philo_list);
}
