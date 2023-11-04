/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baby_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:16:19 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/04 16:33:36 by psimcak          ###   ########.fr       */
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
		ft_ra(head);
	else if (max_node == (*head)->next)
		ft_rra(head);
	if ((*head)->value > (*head)->next->value)
		ft_sa(head);
}
