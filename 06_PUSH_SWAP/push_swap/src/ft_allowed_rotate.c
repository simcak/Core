/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allowed_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:56:23 by peta              #+#    #+#             */
/*   Updated: 2023/10/23 10:50:00 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	rotate(t_node **head)
{
	t_node	*first_node;
	t_node	*second_node;
	t_node	*last_node;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return ;
	first_node = *head;
	second_node = first_node->next;
	last_node = ft_find_last_node(*head);
	if (last_node == NULL)
		return ;
	first_node->next = NULL;
	first_node->prev = last_node;
	last_node->next = first_node;
	second_node->prev = NULL;
	*head = second_node;
}

void	ft_ra(t_node **a, bool checker)
{
	rotate(a);
	if (!checker)
		write(1, "ra\n", 3);
}

void	ft_rb(t_node **b, bool checker)
{
	rotate(b);
	if (!checker)
		write(1, "rb\n", 3);
}

void	ft_rr(t_node **a, t_node **b, bool checker)
{
	rotate(a);
	rotate(b);
	if (!checker)
		write(1, "rr\n", 3);
}
