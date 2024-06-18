/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:52:35 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/18 17:12:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_global_rules(t_global_rules *g_rules, char **argv)
{
	g_rules->number_of_philosophers = ft_atoi(argv[1]);
	g_rules->time_to_die = ft_atoi(argv[2]);
	g_rules->time_to_eat = ft_atoi(argv[3]);
	g_rules->time_to_sleep = ft_atoi(argv[4]);
}

// Create a new philosopher
t_philosopher *create_philosopher(int id, int die_time, int eat_time, int sleep_time)
{
	t_philosopher *new_philosopher;

	new_philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!new_philosopher)
		return NULL;
	new_philosopher->id = id;
	new_philosopher->time_to_die = die_time;
	new_philosopher->time_to_eat = eat_time;
	new_philosopher->time_to_sleep = sleep_time;
	new_philosopher->next = NULL;
	return new_philosopher;
}

// Add philosopher to the list
void add_philosopher(t_philosopher **head, t_philosopher *new_philosopher)
{
	t_philosopher	*temp;
	
	if (!head || !new_philosopher)
		return ;
	if (!*head)
		*head = new_philosopher;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_philosopher;
	}
}

// Initialize philosophers list
t_philosopher	*init_philosophers(t_global_rules rules)
{
	t_philosopher	*head;
	t_philosopher	*new_philosopher;
	int				i;

	head = NULL;
	i = -1;
	while (++i < rules.number_of_philosophers)
	{
		new_philosopher = create_philosopher(i + 1, rules.time_to_die, rules.time_to_eat, rules.time_to_sleep);
		if (!new_philosopher)
			return (NULL);
		add_philosopher(&head, new_philosopher);
	}
	return (head);
}

int	main(int argc, char **argv)
{
	t_global_rules	g_rules;
	int				i;

	if (argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	set_global_rules(&g_rules, argv);
	while (i < g_rules.number_of_philosophers)
	{
	}
}
