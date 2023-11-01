/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:10:38 by peta              #+#    #+#             */
/*   Updated: 2023/11/01 16:45:24 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push_swap(t_node **a, t_node **b)
{
	if (ft_lstlen(*a) == 2)
		ft_sa(a);
	if (ft_lstlen(*a) == 3)
		ft_baby_sort_3(a);
	// if (ft_lstlen(*a) == 5)
		// ft_teen_sort_5(a, b);
	if (ft_lstlen(*a) > 5)
		ft_adult_sort(a, b);
}
