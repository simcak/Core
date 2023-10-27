/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:30:49 by peta              #+#    #+#             */
/*   Updated: 2023/10/27 17:42:57 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ft_smallest_node(t_node *list)
{
	long		smallest;
	t_node		*smallest_node;

	if (list == NULL)
		return (NULL);
	smallest = LONG_MAX;
	while (list)
	{
		if (list->value < smallest)
		{
			smallest = list->value;
			smallest_node = list;
		}
		list = list->next;
	}
	return (smallest_node);
}
