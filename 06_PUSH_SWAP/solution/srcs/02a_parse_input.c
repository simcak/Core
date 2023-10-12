/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02a_parse_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 02:49:27 by lwoiton           #+#    #+#             */
/*   Updated: 2023/08/16 16:31:13 by lwoiton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_string(char *argv[], t_list *a)
{
	char	**parsed_params;
	int		i;
	int		rtrn;
	long	nbr;

	parsed_params = ft_split(argv[1], ' ');
	i = 0;
	rtrn = 0;
	while (parsed_params[i] != NULL && rtrn != -1)
	{
		if (check_isnumber(parsed_params[i]) == -1)
			rtrn = -1;
		nbr = ft_atoi(parsed_params[i]);
		if (INT_MIN <= nbr && nbr <= INT_MAX && !check_isduplicated(a, nbr))
			ft_lstadd_back(a, ft_lstnew((int) nbr));
		else
			rtrn = -1;
		++i;
	}
	free(parsed_params);
	return (rtrn);
}

int	parse_args(int argc, char *argv[], t_list *a)
{
	int		i;
	int		rtrn;
	long	nbr;

	i = 1;
	rtrn = 0;
	while (i < argc && rtrn != -1)
	{
		if (check_isnumber(argv[i]) == -1)
			rtrn = -1;
		nbr = ft_atoi(argv[i]);
		if (INT_MIN <= nbr && nbr <= INT_MAX && !check_isduplicated(a, nbr))
			ft_lstadd_back(a, ft_lstnew((int) nbr));
		else
			rtrn = -1;
		i++;
	}
	return (rtrn);
}

int	parse_input(int argc, char *argv[], t_list *a)
{
	int	rtrn;

	rtrn = 0;
	if (argc < 2)
		rtrn = 0;
	else if (argc == 2)
		rtrn = parse_string(argv, a);
	else if (argc > 2)
		rtrn = parse_args(argc, argv, a);
	return (rtrn);
}
