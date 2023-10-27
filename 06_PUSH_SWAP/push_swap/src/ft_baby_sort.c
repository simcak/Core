/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baby_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:16:19 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/27 15:05:01 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_node	*ft_find_max(t_node *head)
{
	t_node	*temp_max;

	if (head == NULL)
		return (NULL);
	temp_max = head;
	while (head)
	{
		if (head->value > temp_max->value)
			temp_max = head;
		head = head->next;
	}
	return (temp_max);
}

void	ft_baby_sort_3(t_node **head)
{
	t_node	*max_node;

	max_node = ft_find_max(*head);
	if (max_node == *head)
		ft_ra(head, false);
	else if (max_node == (*head)->next)
		ft_rra(head, false);
	if ((*head)->value > (*head)->next->value)
		ft_sa(head, false);
}

// void	ft_baby_sort_5(t_node **a, t_node **b)
// {
	
// }
