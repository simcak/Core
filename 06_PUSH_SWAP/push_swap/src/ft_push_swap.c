/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:10:38 by peta              #+#    #+#             */
/*   Updated: 2023/10/27 12:18:28 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push_swap(t_node **a, t_node **b)
{
	if (ft_lstlen(a) == 2)
		ft_sa(&a, false);
	if (ft_lstlen(a) == 3)
		ft_baby_swap_3(&a);
	if (ft_lstlen(a) == 5)
		ft_baby_swap_5(&a);
	else
	{
		
	}
}
