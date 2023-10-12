/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_calculate_costs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:15:17 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/15 13:41:05 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	account_adjacency(t_list *a, t_node *curr_b)
{
	t_node	*curr_a;
	int		steps;
	int		diff;

	curr_a = a->head;
	if (curr_b->ra)
		steps = curr_b->ra;
	else
		steps = curr_b->rra;
	while (steps-- > 0)
		curr_a = curr_a->next;
	diff = curr_a->rank - curr_b->rank;
	curr_b->cost += diff;
	return (0);
}

int	account_chunk_cost(t_list *a, t_node *curr_b)
{
	if (curr_b->rank / a->chunk_size != a->head->rank / a->chunk_size)
		curr_b->cost += NOT_IN_CHUNK_PANELTY;
	return (0);
}

int	calc_costs(t_list *a, t_list *b)
{
	t_node	*curr_b;
	int		iter;

	curr_b = b->head;
	iter = 0;
	while (iter++ < b->size)
	{
		if (curr_b->ra > 0 && curr_b->rb > 0)
			curr_b->cost = max(curr_b->ra, curr_b->rb);
		else if (curr_b->rra > 0 && curr_b->rrb > 0)
			curr_b->cost = max(curr_b->rra, curr_b->rrb);
		else
			curr_b->cost = curr_b->ra + curr_b->rb + curr_b->rrb + curr_b->rra;
		account_chunk_cost(a, curr_b);
		account_adjacency(a, curr_b);
		curr_b = curr_b->next;
	}
	return (0);
}

t_node	*find_min_cost(t_list *b)
{
	t_node	*curr_b;
	t_node	*best_to_move;
	int		min_cost;
	int		inter;

	curr_b = b->head;
	min_cost = curr_b->cost;
	best_to_move = curr_b;
	inter = 0;
	while (inter++ < b->size)
	{
		if (curr_b->cost < min_cost)
		{
			min_cost = curr_b->cost;
			best_to_move = curr_b;
		}
		curr_b = curr_b->next;
	}
	return (best_to_move);
}
