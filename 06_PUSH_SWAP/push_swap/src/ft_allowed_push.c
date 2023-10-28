/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allowed_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:18:16 by peta              #+#    #+#             */
/*   Updated: 2023/10/28 15:37:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push(t_node **dest, t_node **src)
{
	t_node	*moving_node;

	if (src == NULL || *src == NULL || dest == NULL)
		return ;
	moving_node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	moving_node->prev = NULL;
	moving_node->next = NULL;
	if (*dest == NULL)
		*dest = moving_node;
	else
	{
		moving_node->next = *dest;
		moving_node->next->prev = moving_node;
		*dest = moving_node;
	}
}

void	ft_pa(t_node **a, t_node **b)
{
	push(a, b);
	write(1, "pa\n", 3);
}

void	ft_pb(t_node **a, t_node **b)
{
	push(b, a);
	write(1, "pb\n", 3);
}
