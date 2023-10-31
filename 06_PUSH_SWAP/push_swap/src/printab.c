/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:34:50 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/31 18:35:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_printab(t_node **a, t_node **b)
{
	t_node	*temp_a;
	t_node	*temp_b;

	temp_a = *a;
	temp_b = *b;
	while (temp_a || temp_b)
	{
		if (temp_a)
			printf("\t%i", (temp_a)->value);
		else if (!temp_a)
			printf("\t  ");
		if (temp_b)
			printf("\t%i", (temp_b)->value);
		else if (!temp_b)
			printf(" ");
		printf("\n");
		if (temp_a)
			(temp_a) = (temp_a)->next;
		if (temp_b)
			(temp_b) = (temp_b)->next;
	}
	printf("\t_\t_\n");
	printf("\ta\tb\n");
}
