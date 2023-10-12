/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:34:22 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 14:15:24 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error_exit(t_list *a, t_list *b)
{
	ft_printf("Error\n");
	if (a != NULL)
		free_list(a);
	if (b != NULL)
		free_list(b);
	return (-1);
}

int	validate_input(int argc, char *argv[], t_list *a)
{
	if (parse_input(argc, argv, a) == -1)
		return (error_exit(a, NULL));
	if (check_issorted(a) == 1)
	{
		if (argc > 2)
			ft_printf("OK\n");
		free_list(a);
		return (1);
	}
	return (0);
}

int	execute_operation(char *operation, t_list *a, t_list *b)
{
	if (ft_strncmp(operation, "sa\n", 3) == 0)
		swap(a);
	else if (ft_strncmp(operation, "sb\n", 3) == 0)
		swap(b);
	else if (ft_strncmp(operation, "ss\n", 3) == 0)
		swap2(a, b, 0);
	else if (ft_strncmp(operation, "pa\n", 3) == 0)
		push(a, b);
	else if (ft_strncmp(operation, "pb\n", 3) == 0)
		push(b, a);
	else if (ft_strncmp(operation, "ra\n", 3) == 0)
		rotate1(a);
	else if (ft_strncmp(operation, "rb\n", 3) == 0)
		rotate1(b);
	else if (ft_strncmp(operation, "rr\n", 3) == 0)
		rotate2(a, b);
	else if (ft_strncmp(operation, "rra\n", 4) == 0)
		reverse_rotate1(a);
	else if (ft_strncmp(operation, "rrb\n", 4) == 0)
		reverse_rotate1(b);
	else if (ft_strncmp(operation, "rrr\n", 4) == 0)
		reverse_rotate2(a, b);
	else
		return (error_exit(a, b));
	return (0);
}

int	read_operations(t_list *a, t_list *b)
{
	char	*operation;

	operation = get_next_line(0);
	while (operation != NULL)
	{
		if (operation[0] == '\n')
			break ;
		if (execute_operation(operation, a, b) == -1)
			return (-1);
		free(operation);
		operation = get_next_line(0);
	}
	free(operation);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list	a;
	t_list	b;
	int		rtrn;

	ft_list_init(&a, 0);
	ft_list_init(&b, 0);
	rtrn = validate_input(argc, argv, &a);
	if (rtrn == -1 || rtrn == 1)
		return (rtrn);
	if (read_operations(&a, &b) == -1)
		return (-1);
	if (check_issorted(&a) == 1 && b.head == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_list(&a);
	free_list(&b);
	return (0);
}
