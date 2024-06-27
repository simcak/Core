/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:14:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/27 17:06:05 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//******************************** LIBRARIES *********************************//
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

//******************************* ANSI COLORES *******************************//
# define R		"\033[1;31m"
# define G		"\033[1;32m"
# define B		"\033[1;34m"
# define Y		"\033[1;33m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"
# define RST	"\033[0m"

//********************************** MACROS **********************************//
# define SUCCESS	0
# define FAILURE	1

typedef pthread_mutex_t	t_mutex;
//******************************** STRUCTURES ********************************//
typedef struct s_fork
{
	long			id;
	t_mutex			fork_mutex;
}	t_fork;

typedef struct s_philo
{
	long			id;
	pthread_t		thread_id;
	long			meals_counter;
	long			last_meal_time_ms;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
}	t_philos;

typedef struct s_dinner
{
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_dinner;
	bool			end_dinner;
	t_fork			*forks;
	t_philos		*philos;
}	t_dinner;

//******************************* ENUMERATION ********************************//
typedef enum e_func_type
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
} t_func_type;

//******************************** PROTOTYPES ********************************//
// DINER_FUNCTIONS
int					prepare_dinner(t_dinner *dinner, char **argv);

// LIBFT_PHILO
long				ft_atol(char *argv_i);
int					ft_strlen(char *str);

#endif
