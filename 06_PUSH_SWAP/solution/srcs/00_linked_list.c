/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_linked_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:01:25 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/15 13:43:14 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_list_init(t_list *list, char c)
{
	list->id = c;
	list->size = 0;
	list->chunk_nr = 0;
	list->chunk_size = 0;
	list->min_rank = INT_MAX;
	list->max_rank = INT_MIN;
	list->head = NULL;
}

t_node	*ft_lstnew(int content)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->content = content;
	new->rank = 0;
	new->cost = 0;
	new->ra = 0;
	new->rb = 0;
	new->rra = 0;
	new->rrb = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_lstadd_back(t_list *list, t_node *node)
{
	t_node	*temp;

	list->size += 1;
	if (list->head == NULL)
	{
		list->head = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		temp = list->head;
		while (temp->next != list->head)
		{
			temp = temp->next;
		}
		node->next = list->head;
		list->head->prev = node;
		node->prev = temp;
		temp->next = node;
	}
	return (0);
}

int	free_list(t_list *list)
{
	t_node	*tmp;

	if (list->head == NULL)
		return (0);
	while (list->head != list->head->next)
	{
		tmp = list->head;
		list->head->prev->next = list->head->next;
		list->head->next->prev = list->head->prev;
		list->head = list->head->next;
		free(tmp);
	}
	free(list->head);
	return (0);
}
