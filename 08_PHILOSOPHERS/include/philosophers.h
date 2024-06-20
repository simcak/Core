/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:14:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/19 20:06:12 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//********** LIBRARIES ***********//
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

//********** STRUCTURES **********//
typedef struct s_global_rules
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
}	t_global_rules;

typedef struct s_philosopher
{
	int						id;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	struct s_philosopher	*next;
}	t_philosopher;

//********** PROTOTYPES **********//
// INIT_FILES
t_philosopher	*init_list_of_philosophers(t_global_rules rules);
void			set_global_rules(t_global_rules *g_rules, char **argv);

// LIBFT_PHILO
int				ft_atoi(const char *str);
int				ft_strlen(char *str);

#endif
