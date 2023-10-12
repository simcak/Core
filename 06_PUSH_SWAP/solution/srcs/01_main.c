/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:57:19 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/15 16:56:16 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort(t_list *a)
{
	t_list	b;
	t_node	*sel_node;

	ft_list_init(&b, 'b');
	analyse_ranks(a);
	divide_into_chunks(a, &b);
	sort_five(a, &b);
	while (b.size > 0)
	{
		calc_rotations(a, &b);
		calc_costs(a, &b);
		sel_node = find_min_cost(&b);
		push_sel_node(a, &b, sel_node);
	}
	final_rotation(a);
}

int	main(int argc, char *argv[])
{
	t_list	a;

	ft_list_init(&a, 'a');
	if (parse_input(argc, argv, &a) == -1)
	{
		ft_printf("Error\n");
		free_list(&a);
		return (0);
	}
	if (!check_issorted(&a))
		sort(&a);
	free_list(&a);
	return (0);
}
