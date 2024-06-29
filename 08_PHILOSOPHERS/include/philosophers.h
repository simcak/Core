/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:14:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/06/29 14:06:02 by psimcak          ###   ########.fr       */
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
# include <errno.h>

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
typedef pthread_t		t_thread;
//******************************** STRUCTURES ********************************//
typedef struct s_fork
{
	long			id;
	t_mutex			fork_mutex;
}	t_fork;

typedef struct s_philo
{
	long			id;
	t_thread		thread_id;
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
}	t_func_type;

//******************************** PROTOTYPES ********************************//
// DINER_FUNCTIONS
int					prepare_dinner(t_dinner *dinner, char **argv);

// ERROR_POLICE
int					args_are_invalid(t_dinner *dinner);

// LIB_PHILO
long				ft_atol(char *argv_i);
int					ft_strlen(char *str);
bool				philo_id_is_odd(t_philos *philo);
bool				philo_id_is_even(t_philos *philo);
int					safe_mutex(t_mutex *mutex, t_func_type type);
int					safe_thread(t_thread *thread, t_func_type type,
						void *(*func)(void *), void *data);

//****************************** ERROR MESSAGES ******************************//
// Mutex
# define ERR_EINVAL_MUTEX_LUD \
		"The value specified by mutex is invalid.\n"
# define ERR_EINVAL_MUTEX_I \
		"The value specified by attr is invalid.\n"
# define ERR_EDEADLK_MUTEX \
		"A deadlock would occur if the thread blocked waiting for mutex.\n"
# define ERR_EPERM_MUTEX \
		"The current thread does not hold a lock on mutex.\n"
# define ERR_ENOMEM_MUTEX \
		"The process cannot allocate enough memory to create another mutex.\n"
# define ERR_EBUSY_MUTEX "Mutex is locked.\n"

// Thread
# define ERR_EAGAIN_THREAD \
		"The system lacked the necessary resources to create another thread, o\
		r the system-imposed limit on the total number of threads in a process \
		[PTHREAD_THREADS_MAX] would be exceeded.\n"
# define ERR_EPERM_THREAD \
		"The caller does not have appropriate permission to set the required sc\
		heduling parameters or scheduling policy.\n"
# define ERR_EINVAL_THREAD_C \
		"The value specified by attr is invalid.\n"
# define ERR_EINVAL_THREAD_JD \
		"The implementation has detected that the value specified by thread doe\
		s not refer to a joinable thread.\n"
# define ERR_ESRCH_THREAD \
		"No thread could be found corresponding to that specified by the given \
		thread ID, thread.\n"
# define ERR_EDEADLK_THREAD \
		"A deadlock was detected or the value of thread specifies the calling t\
		hread.\n"

#endif
