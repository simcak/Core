/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02b_check_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:09:27 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 13:16:42 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_isnumber(char *str)
{
	int	i;
	int	rtrn;

	i = 0;
	rtrn = 0;
	while (str[i] && rtrn != -1)
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			rtrn = -1;
		i++;
	}
	return (rtrn);
}

int	check_issorted(t_list *a)
{
	t_node	*curr_a;
	int		rtrn;

	if (a->head == NULL)
		return (1);
	curr_a = a->head;
	rtrn = 1;
	while (curr_a->next != a->head)
	{
		if (curr_a->content > curr_a->next->content)
			rtrn = 0;
		curr_a = curr_a->next;
	}
	return (rtrn);
}

int	check_isduplicated(t_list *a, int nbr)
{
	t_node	*curr_a;
	int		rtrn;

	curr_a = a->head;
	rtrn = 0;
	if (a->head == NULL)
		return (rtrn);
	while (curr_a->next != a->head)
	{
		if (curr_a->content == nbr)
			rtrn = -1;
		curr_a = curr_a->next;
	}
	if (curr_a->content == nbr)
		rtrn = -1;
	return (rtrn);
}
