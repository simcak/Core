/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adult_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:47:38 by peta              #+#    #+#             */
/*   Updated: 2023/11/01 16:47:52 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_up_from_median(t_node *list)
{
	int	i;
	int	median_index;

	i = 0;
	if (list == NULL)
		return ;
	median_index = ft_lstlen(list) / 2;
	while (list)
	{
		list->current_index = i;
		if (i <= median_index)
			list->up_from_median = true;
		else
			list->up_from_median = false;
		list = list->next;
		i++;
	}
}

// potential error maker

void	ft_aim(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*aimed_node;
	long	best_match;

	while (b)
	{
		best_match = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value
				&& current_a->value < best_match)
			{
				best_match = current_a->value;
				aimed_node = current_a;
			}
			current_a = current_a->next;
		}
		if (LONG_MAX == best_match)
			b->aimed_node = ft_find_smallest(a);
		else
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
		return (NULL);
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
