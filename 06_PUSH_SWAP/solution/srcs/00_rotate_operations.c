/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_rotate_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:09:25 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 13:16:47 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotate1(t_list *list)
{
	if (list->head == NULL)
		return (-1);
	list->head = list->head->next;
	if (list->id != 0)
		ft_printf("r%c\n", list->id);
	return (0);
}

int	rotate2(t_list *a, t_list *b)
{
	if (a->head == NULL || b->head == NULL)
		return (-1);
	a->head = a->head->next;
	b->head = b->head->next;
	if (a->id != 0 && b->id != 0)
		ft_printf("rr\n");
	return (0);
}

int	reverse_rotate1(t_list *list)
{
	if (list->head == NULL)
		return (-1);
	list->head = list->head->prev;
	if (list->id != 0)
		ft_printf("rr%c\n", list->id);
	return (0);
}

int	reverse_rotate2(t_list *a, t_list *b)
{
	if (a->head == NULL || b->head == NULL)
		return (-1);
	a->head = a->head->prev;
	b->head = b->head->prev;
	if (a->id != 0 && b->id != 0)
		ft_printf("rrr\n");
	return (0);
}
