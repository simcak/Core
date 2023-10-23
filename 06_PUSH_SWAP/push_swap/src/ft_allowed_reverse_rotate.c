/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allowed_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:05:35 by peta              #+#    #+#             */
/*   Updated: 2023/10/23 11:16:06 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	reverse_rotate(t_node **head)
{
	t_node	*first_node;
	t_node	*prev_last_node;
	t_node	*last_node;

	if (head == NULL || *head == NULL)
		return ;
	first_node = *head;
	last_node = ft_find_last_node(*head);
	if (last_node == NULL || last_node->prev == NULL)
		return ;
	prev_last_node = last_node->prev;
	last_node->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	prev_last_node->next = NULL;
	*head = last_node;
}

void	ft_rra(t_node **a, bool checker)
{
	reverse_rotate(a);
	if (!checker)
		write(1, "rra\n", 4);
}

void	ft_rrb(t_node **b, bool checker)
{
	reverse_rotate(b);
	if (!checker)
		write(1, "rrb\n", 4);
}

void	ft_rrr(t_node **a, t_node **b, bool checker)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!checker)
		write(1, "rrr\n", 4);
}
