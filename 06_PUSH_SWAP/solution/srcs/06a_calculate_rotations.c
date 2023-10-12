/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_calculate_rotations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:17:26 by lwoiton           #+#    #+#             */
/*   Updated: 2023/07/22 06:24:46 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_rotations(t_list *a, t_list *b)
{
	t_node	*curr_b;
	int		next_rank;
	int		rotations;

	curr_b = b->head;
	rotations = 0;
	reset_rotations(b);
	while (rotations < b->size)
	{
		curr_b->rb = rotations;
		curr_b = curr_b->next;
		if (curr_b->rank < a->min_rank)
			curr_b->ra = get_rotations_a(a, a->min_rank);
		else
		{
			next_rank = get_next_rank(a, curr_b->rank);
			curr_b->ra = get_rotations_a(a, next_rank);
		}
		rotations++;
	}
	set_rotation_direction(a, b);
	return (0);
}

int	get_rotations_a(t_list *a, int next_rank)
{
	int		rotations;
	t_node	*curr_a;

	rotations = 0;
	curr_a = a->head;
	while (curr_a->rank != next_rank)
	{
		curr_a = curr_a->next;
		rotations++;
	}
	return (rotations);
}

int	reset_rotations(t_list *b)
{
	t_node	*curr_b;
	int		iter;

	curr_b = b->head;
	iter = 0;
	while (iter++ < b->size)
	{
		curr_b->rb = 0;
		curr_b->rrb = 0;
		curr_b->ra = 0;
		curr_b->rra = 0;
		curr_b = curr_b->next;
	}
	return (0);
}

int	set_rotation_direction(t_list *a, t_list *b)
{
	t_node	*curr_b;
	int		iter;

	curr_b = b->head;
	iter = 0;
	while (iter++ < b->size)
	{
		if (curr_b->rb > b->size / 2)
		{
			curr_b->rrb = b->size - curr_b->rb;
			curr_b->rb = 0;
		}
		if (curr_b->ra > a->size / 2)
		{
			curr_b->rra = a->size - curr_b->ra;
			curr_b->ra = 0;
		}
		curr_b = curr_b->next;
	}
	return (0);
}
