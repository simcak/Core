/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ranks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:14:02 by lwoiton           #+#    #+#             */
/*   Updated: 2023/07/22 03:14:16 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_rank(t_list *a)
{
	t_node	*curr_a;
	int		min_rank;
	int		iter;

	curr_a = a->head;
	min_rank = curr_a->rank;
	iter = 0;
	while (iter++ < a->size)
	{
		if (curr_a->rank < min_rank)
			min_rank = curr_a->rank;
		curr_a = curr_a->next;
	}
	return (min_rank);
}

int	get_max_rank(t_list *a)
{
	t_node	*curr_a;
	int		max_rank;
	int		iter;

	curr_a = a->head;
	max_rank = -1;
	iter = 0;
	while (iter++ < a->size)
	{
		if (curr_a->rank > max_rank)
			max_rank = curr_a->rank;
		curr_a = curr_a->next;
	}
	return (max_rank);
}

int	get_next_rank(t_list *a, int curr_rank_bn)
{
	t_node	*curr_a;
	int		next_rank;
	int		iter;

	curr_a = a->head;
	next_rank = a->max_rank;
	iter = 0;
	while (iter < a->size)
	{
		if (curr_a->rank > curr_rank_bn && curr_a->rank < next_rank)
			next_rank = curr_a->rank;
		curr_a = curr_a->next;
		iter++;
	}
	return (next_rank);
}
