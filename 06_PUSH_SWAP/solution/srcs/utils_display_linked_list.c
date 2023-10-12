/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display_linked_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 02:57:38 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/10 14:22:38 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	display_list(t_list *list)
{
	t_node	*curr_n;

	curr_n = list->head;
	if (curr_n == NULL)
	{
		ft_printf("List is empty.\n");
		return ;
	}
	ft_printf("Linked List: ");
	while (curr_n->next != list->head)
	{
		ft_printf("%d(%d,%d) ", curr_n->content, \
			curr_n->rank, curr_n->rank / list->chunk_size);
		curr_n = curr_n->next;
	}
	ft_printf("%d(%d,%d)\n", curr_n->content, \
		curr_n->rank, curr_n->rank / list->chunk_size);
	ft_printf("\nSize: %d\n", list->size);
}

void	print_stacks_head(void)
{
	ft_printf("+---------+------+-------+------+----+----+-----+-----+\
	   +---------+------+-------+------+----+----+-----+-----+\n");
	ft_printf("| Stack A | rank | chunk | cost | ra | rb | rra | rrb |\
	   | Stack B | rank | chunk | cost | ra | rb | rra | rrb |\n");
	ft_printf("+---------+------+-------+------+----+----+-----+-----+\
	   +---------+------+-------+------+----+----+-----+-----+\n");
}

void	print_stack(t_node *node, int cs, int size_a)
{
	if (size_a > 0)
	{
		ft_printf("|%9d|%6d|%7d|%6d|%4d|%4d|%5d|%5d|    ", \
			node->content, node->rank, node->rank / cs, node->cost, \
			node->ra, node->rb, node->rra, node->rrb);
	}
	else
	{
		ft_printf("|%9s|%6s|%7s|%6s|%4s|%4s|%5s|%5s|    ", \
			"-", "-", "-", "-", "-", "-", "-", "-");
	}
}

void	print_stacks(t_list *a, t_list *b)
{
	int		size_a;
	int		size_b;

	size_a = a->size;
	size_b = b->size;
	if (a->head == NULL && b->head == NULL)
	{
		ft_printf("Error\n");
		return ;
	}
	print_stacks_head();
	while (size_b > 0 || size_a > 0)
	{
		print_stack(a->head, a->chunk_size, size_a);
		if (a->head && size_a-- > 0)
			a->head = a->head->next;
		print_stack(b->head, a->chunk_size, size_b);
		if (b->head && size_b-- > 0)
			b->head = b->head->next;
		ft_printf("\n");
	}
}
