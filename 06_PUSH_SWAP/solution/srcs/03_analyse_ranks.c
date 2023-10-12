/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_analyse_ranks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:42:45 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/15 12:54:33 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	cur;
	int	buff;

	i = 0;
	while (i < size - 1)
	{
		cur = i + 1;
		while (cur < size)
		{
			if (tab[i] > tab[cur])
			{
				buff = tab[cur];
				tab[cur] = tab[i];
				tab[i] = buff;
			}
			++cur;
		}
		++i;
	}
}

void	assign_ranks(t_list *a, int *sorted_a)
{
	t_node	*curr_a;
	int		iter;
	int		rank;

	curr_a = a->head;
	iter = 0;
	while (iter++ < a->size)
	{
		rank = 0;
		while (rank < a->size)
		{
			if (sorted_a[rank] == curr_a->content)
			{
				curr_a->rank = rank;
				break ;
			}
			rank++;
		}
		curr_a = curr_a->next;
	}
}

void	analyse_ranks(t_list *a)
{
	t_node	*curr_a;
	int		*sorted_a;
	int		iter;

	curr_a = a->head;
	sorted_a = (int *) malloc(a->size * sizeof(int));
	iter = 0;
	set_chunk_nr(a);
	while (iter < a->size)
	{
		sorted_a[iter] = curr_a->content;
		curr_a = curr_a->next;
		iter++;
	}
	ft_sort_int_tab(sorted_a, a->size);
	assign_ranks(a, sorted_a);
	a->min_rank = get_min_rank(a);
	a->max_rank = get_max_rank(a);
	free(sorted_a);
}
