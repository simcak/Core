/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adult_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:07:21 by peta              #+#    #+#             */
/*   Updated: 2023/10/28 16:19:43 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_locker_rotation(t_node *head, t_node *stop_node, char name)
{
	if (stop_node->up_from_median)
		while (head != stop_node)
		{
			if (name == 'a')
				ft_ra(head);
			if (name == 'b')
				ft_rb(head);
		}
	else
		while (head != stop_node)
		{
			if (name == 'a')
				ft_rra(head);
			if (name == 'b')
				ft_rrb(head);
		}
	
}

static void	ft_shoot(t_node *a, t_node *b)
{
	t_node *chpst;

	chpst = ft_cheapest(b);
	if (chpst->up_from_median && chpst->aimed_node->up_from_median)
	{
		while (chpst != b && chpst->aimed_node != a)
			ft_rr(a, b);
	}
	else if (!(chpst->up_from_median) && !(chpst->aimed_node->up_from_median))
	{
		while (chpst != b && chpst->aimed_node != a)
			ft_rrr(a, b);
	}
	ft_up_from_median(a);
	ft_up_from_median(b);
	ft_locker_rotation(a, chpst->aimed_node, 'a');
	ft_locker_rotation(b, chpst, 'b');
	ft_pa(a, b);
}

void	ft_adult_sort(t_node **a, t_node **b)
{
	while (ft_lstlen(*a) > 3)
		ft_pa(a, b);
	ft_baby_sort_3(a);
	while (*b)
	{
		ft_up_from_median(*a);
		ft_up_from_median(*b);
		ft_aim(*a, *b);
		ft_how_much_it_cost(*a, *b);
		ft_shoot(*a, *b);
	}
	ft_final_rotation(*a);
}
