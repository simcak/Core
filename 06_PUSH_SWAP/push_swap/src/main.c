/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:25 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/31 17:20:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_printa(t_node **a)
{
	t_node	*temp_a;

	temp_a = *a;
	while (temp_a)
	{
		printf("\t%i\n", (temp_a)->value);
		(temp_a) = (temp_a)->next;
	}
}

int	main(int argc, char *argv[])
{
	t_node	*a;
	t_node	*b;

	a = NULL;
	b = NULL;
	if (argc <= 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');
	ft_create_stack(&a, argv);
	ft_printa(&a); // SMAZAT !!!
	if (!sorted_stack(a))
	 	ft_push_swap(&a, &b);
	// free_stack();
	if (sorted_stack(a)) // SMAZAT !!!
		write(1, "OK\n", 3); // SMAZAT !!!
	ft_printa(&a); // SMAZAT !!!
	return (0);
}
