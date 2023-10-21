/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:55:03 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/21 15:53:59 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ft_find_last_node(t_node *list_head)
{
	if (list_head == NULL)
		return (NULL);
	while (list_head->next)
		list_head = list_head->next;
	return (list_head);
}

void	ft_crate_append_node(t_node **list, int num)
{
	t_node	*node;
	t_node	*last_node;

	if (list == NULL)
		return ;
	node = malloc(sizeof(t_node));
	if (node == NULL)
		return ;
	node->value = num;
	node->next = NULL;
	if (*list == NULL)
	{
		*list = node;
		node->prev = NULL;
	}
	else
	{
		last_node = ft_find_last_node(*list);
		last_node->next = node;
		node->prev = last_node;
	}
}

void	ft_create_list(t_node **list, char **argv)
{
	long	nbr;
	int		i;

	i = 0;
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			exit(1);
		ft_crate_append_node(list, (int)nbr);
		i++;
	}
}
