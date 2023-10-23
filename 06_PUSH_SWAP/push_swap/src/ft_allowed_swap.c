/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allowed_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:36:01 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/23 10:34:13 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap(t_node **head)
{
	t_node	*first;
	t_node	*second;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return ;
	first = *head;
	second = (*head)->next;
	*head = second;
	first->next = second->next;
	first->prev = second;
	if (second->next)
		second->next->prev = first;
	second->next = first;
	second->prev = NULL;
}

void	ft_sa(t_node **a, bool checker)
{
	swap(a);
	if (!checker)
		write(1, "sa\n", 3);
}

void	ft_sb(t_node **b, bool checker)
{
	swap(b);
	if (!checker)
		write(1, "sb\n", 3);
}

void	ft_ss(t_node **a, t_node **b, bool checker)
{
	swap(a);
	swap(b);
	if (!checker)
		write(1, "ss\n", 3);
}
