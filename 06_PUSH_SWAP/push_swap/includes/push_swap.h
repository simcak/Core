/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:15 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/21 15:55:01 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

/*
value: acuall value of the node
rank: rank is the position of the 'value' in the final, sorted output
cost: how far away is 'value' from the 'rank'
*/
typedef struct s_node
{
	int				value;
	int				rank;
	int				cost;
	int				size;

	struct s_node	*next;
	struct s_node	*prev;
	
}	t_node;

char	**ft_split(char const *s, char c);
void	ft_create_list(t_node **list, char **argv);
long	ft_atol(char *argv_i);

#endif