/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:22:58 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/11 18:02:30 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_table	t_table;

typedef enum e_mutex
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}	t_mutex;

typedef enum e_mutex
{
	CREATE,
	JOIN,
	DETACH,
}	t_thread;

typedef enum e_time
{
	MILLI_SEC,
	MICRO_SEC,
}	t_time;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			last_time_eaten;
	long			meals_eaten;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}					t_philo;

/*philos_ready is a bool that turns to true, when all
philo threads are made*/
typedef struct s_table
{
	long			num_philos;
	long			to_die;
	long			to_eat;
	long			to_sleep;
	long			limit_meals;
	long			dead_philo;
	long			start_time;
	long			all_full;
	bool			end_simulation;
	bool			philos_ready;
	pthread_mutex_t	read_table;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
	t_fork			*forks;
}			t_table;

//________PROTOTYPES________
/*dinner.c*/
void	start_dinner(t_table *table);

/*getter_setter.c*/
long	get_long(long *src, pthread_mutex_t *mutex);
void	set_long(long value, long *dest, pthread_mutex_t *mutex);
bool	get_bool(bool *src, pthread_mutex_t *mutex);
bool	set_bool(bool value, bool *dest, pthread_mutex_t *mutex);
bool	simulation_finished(t_table *table);

/*utils.c*/
long	ft_atol(const char *nptr);
void	set_table(t_table *table);
void	wait_all_philos(t_table *table);
long	ft_gettime(t_time type);
void	better_usleep(long usec, t_table *table);

/*handle_func.c*/
void	handle_mutex(pthread_mutex_t *mutex, t_mutex type);
void	handle_thread(pthread_t *thread_id, void *(*foo)(void *),
			void *data, t_thread type);
void	*handle_malloc(size_t size);
/*init.c*/

void	parse_input(t_table *table, char **av);
/*main.c*/

void	error_exit(char *error_msg);

#endif