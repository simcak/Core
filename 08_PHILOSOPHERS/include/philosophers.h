/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:14:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/22 03:20:39 by psimcak          ###   ########.fr       */
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
# define ERROR		7
# define SUCCESS	0
# define FAILURE	1
# define EVEN		0
# define ODD		3
# define MILISEC	0
# define MICROSEC	1
# define NO_LIMIT	-1

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_dinner	t_dinner;
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
	bool			full;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_mutex			philo_mutex;
	t_dinner		*dinner;
}	t_philos;

typedef struct s_dinner
{
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	long			num_of_dining_philos;
	long			meal_limit;
	bool			all_philos_ready;
	bool			finish_dinner;
	t_thread		monitor;
	t_mutex			dinner_mutex;
	t_mutex			print_mutex;
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

typedef enum e_philo_action
{
	TAKE_LF,
	TAKE_RF,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_status;

//******************************** PROTOTYPES ********************************//
// DINER_FUNCTIONS
int					prepare_dinner(t_dinner *dinner, char **argv);
int					start_dinner(t_dinner *dinner);
int					philo_think(t_philos *philo, bool before);
int					philo_eat(t_philos *philo);
bool				philo_died(t_philos *philo);
void				clean(t_dinner *dinner);

// ERROR_POLICE
int					args_are_invalid(t_dinner *dinner);

// LIB_PHILO
long				ft_atol(char *argv_i);
bool				get_bool(t_mutex *mutex, bool *val);
void				set_bool(t_mutex *mutex, bool *dest, bool val);
long				get_long(t_mutex *mutex, long *val);
void				set_long(t_mutex *mutex, long *dest, long val);
void				increse_long(t_mutex *mutex, long *num);
int					safe_mutex(t_mutex *mutex, t_func_type type);
int					safe_thread(t_thread *thread, t_func_type type,
						void *(*func)(void *), void *data);
long				get_precise_time(int type);
void				ft_usleep(long sleep_time, t_dinner *dinner);
int					philo_id_is(t_philos *philo);
int					ft_strlen(char *str);
bool				dinner_finished(t_dinner *dinner);
bool				all_philos_dining(t_dinner *dinner, t_mutex *mutex);
void				write_status(t_philos *philo, t_status action);

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
