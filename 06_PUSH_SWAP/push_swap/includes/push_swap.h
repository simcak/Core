/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:15 by psimcak           #+#    #+#             */
/*   Updated: 2023/10/25 18:52:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

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
void	ft_create_stack(t_node **list, char **argv);
long	ft_atol(char *argv_i);
bool	sorted_stack(t_node *list);
int		ft_lstlen(t_node *list);
void	ft_baby_swap(t_node **head);
t_node	*ft_find_last_node(t_node *list_head);

void	ft_sa(t_node **a, bool checker);
void	ft_sb(t_node **b, bool checker);
void	ft_ss(t_node **a, t_node **b, bool checker);
void	ft_ra(t_node **a, bool checker);
void	ft_rb(t_node **b, bool checker);
void	ft_rr(t_node **a, t_node **b, bool checker);
void	ft_rra(t_node **a, bool checker);
void	ft_rrb(t_node **b, bool checker);
void	ft_rrr(t_node **a, t_node **b, bool checker);
void	ft_pa(t_node **a, t_node **b, bool checker);
void	ft_pb(t_node **a, t_node **b, bool checker);

#endif