/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adult_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:47:38 by peta              #+#    #+#             */
/*   Updated: 2023/10/28 15:23:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_set_current_index(t_node *list)
{
	int	counter;

	if (list == NULL)
		return ;
	counter = 0;
	while (list)
	{
		list->current_index = counter;
		counter++;
		list = list->next;
	}
}

void	ft_up_from_median(t_node *list)
{
	int	median_index;

	if (list == NULL)
		return ;
	ft_set_current_index(list);
	median_index = ft_lstlen(list) / 2;
	while (median_index > 0)
	{
		list->up_from_median = true;
		list = list->next;
		median_index--;
	}
	while (list)
	{
		list->up_from_median = false;
		list = list->next;
	}
}

// potential error maker

void	ft_aim(t_node *a, t_node *b)
{
	t_node	*temp_a;
	t_node	*aimed_node;

	while (b)
	{
		temp_a = a;
		aimed_node = a;
		while (temp_a)
		{
			if (b->value < temp_a->value)
				aimed_node = temp_a;
			temp_a = temp_a->next;
		}
		b->aimed_node = aimed_node;
		b = b->next;
	}
}

void	ft_how_much_it_cost(t_node *a, t_node *b)
{
	while (b)
	{
		b->cost = b->current_index;
		if (!(b->up_from_median))
			b->cost = ft_lstlen(b) - (b->current_index);
		if (b->aimed_node->up_from_median)
			b->cost += b->aimed_node->current_index;
		else
			b->cost += ft_lstlen(a) - (b->aimed_node->current_index);
		b = b->next;
	}
}

t_node	*ft_cheapest(t_node *list)
{
	long	lowest_value_in_list;
	t_node	*cheapest_node;

	if (list == NULL)
		return ;
	lowest_value_in_list = LONG_MAX;
	while (list)
	{
		if (list->cost < lowest_value_in_list)
		{
			lowest_value_in_list = list->value;
			cheapest_node = list;
		}
		list = list->next;
	}
	cheapest_node->cheapest = true;
	return (cheapest_node);
}
