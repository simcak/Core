/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adult_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:07:21 by peta              #+#    #+#             */
/*   Updated: 2023/10/27 17:22:18 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_adult_sort(t_node **a, t_node **b)
{
	while (ft_lstlen(*a) > 3)
		ft_pa(a, b, false);
	ft_baby_sort_3(a);
	while (*b)
	{
		ft_up_from_median(*a);
		ft_up_from_median(*b);
		ft_aim(*a, *b);
		ft_how_much_it_cost(*a, *b);
		ft_cheapest(*b);
		ft_shoot(*a, *b);
	}
	ft_locker_rotation(*a);
}
