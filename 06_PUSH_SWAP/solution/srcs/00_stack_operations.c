/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_stack_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:10:27 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 14:15:46 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(t_list *list)
{
	if (list->head == NULL)
		return (-1);
	list->head->prev->next = list->head->next;
	list->head->next->prev = list->head->prev;
	list->head->prev = list->head->next;
	list->head->next = list->head->next->next;
	list->head->prev->next = list->head;
	list->head->next->prev = list->head;
	list->head = list->head->prev;
	if (list->id != 0)
		ft_printf("s%c\n", list->id);
	return (0);
}

int	swap2(t_list *a, t_list *b, int print)
{
	a->id = 0;
	b->id = 0;
	swap(a);
	swap(b);
	if (print == 1)
	{
		ft_printf("ss\n");
		a->id = 'a';
		b->id = 'b';
	}
	return (0);
}

void	relink_first_node_for_push(t_list *dst, t_list *src)
{
	dst->head = src->head;
	src->head->next->prev = src->head->prev;
	src->head->prev->next = src->head->next;
	src->head = src->head->next;
	dst->head->next = dst->head;
	dst->head->prev = dst->head;
	return ;
}

void	relink_last_node_for_push(t_list *dst, t_list *src)
{
	src->head->next = dst->head;
	src->head->prev = dst->head->prev;
	dst->head->prev->next = src->head;
	dst->head->prev = src->head;
	dst->head = src->head;
	src->head = NULL;
	return ;
}

int	push(t_list *dst, t_list *src)
{
	if (src->head == NULL)
		return (-1);
	if (dst->head == NULL )
		relink_first_node_for_push(dst, src);
	else if (src->head->next == src->head)
		relink_last_node_for_push(dst, src);
	else
	{
		src->head->next->prev = src->head->prev;
		src->head->prev->next = src->head->next;
		dst->head->prev->next = src->head;
		src->head->prev = dst->head->prev;
		dst->head->prev = src->head;
		src->head = src->head->next;
		dst->head->prev->next = dst->head;
		dst->head = dst->head->prev;
	}
	dst->size += 1;
	src->size -= 1;
	if (dst->id != 0)
		ft_printf("p%c\n", dst->id);
	return (0);
}
