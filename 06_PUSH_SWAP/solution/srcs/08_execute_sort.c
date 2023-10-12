/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_execute_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:51:30 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/15 17:12:15 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	execute_double_rotation(t_list *a, t_list *b, t_node *sel_node)
{
	while (sel_node->ra > 0 && sel_node->rb > 0)
	{
		rotate2(a, b);
		sel_node->ra--;
		sel_node->rb--;
	}
	while (sel_node->rra > 0 && sel_node->rrb > 0)
	{
		reverse_rotate2(a, b);
		sel_node->rra--;
		sel_node->rrb--;
	}
}

void	execute_rotation_a(t_list *a, t_node *sel_node)
{
	while (sel_node->ra > 0)
	{
		rotate1(a);
		sel_node->ra--;
	}
	while (sel_node->rra > 0)
	{
		reverse_rotate1(a);
		sel_node->rra--;
	}
}

void	execute_rotation_b(t_list *b, t_node *sel_node)
{
	while (sel_node->rb > 0)
	{
		rotate1(b);
		sel_node->rb--;
	}
	while (sel_node->rrb > 0)
	{
		reverse_rotate1(b);
		sel_node->rrb--;
	}
}

int	push_sel_node(t_list *a, t_list *b, t_node *sel_node)
{
	execute_double_rotation(a, b, sel_node);
	execute_rotation_a(a, sel_node);
	execute_rotation_b(b, sel_node);
	push(a, b);
	a->max_rank = get_max_rank(a);
	a->min_rank = get_min_rank(a);
	return (0);
}

int	final_rotation(t_list *a)
{
	a->max_rank = get_max_rank(a);
	while (a->head->rank != 0)
	{
		if (a->head->rank >= a->max_rank / 2)
			rotate1(a);
		else
			reverse_rotate1(a);
	}
	return (0);
}
