/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:18:48 by tstelken          #+#    #+#             */
/*   Updated: 2026/02/02 12:43:43 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_table *table)
{
	if (0 == status)
		return ;
	if (EBUSY == status)
		error_exit("Mutex is locked", table);
	else if (ENOMEM == status)
		error_exit("Allocation of mutex failed", table);
	else if (EPERM == status)
		error_exit("Thread does not hold a lock on mutex", table);
	else
		error_exit("Mutex error", table);
}

/*Function calls the corresponding pthead_mutex-function and
stops the programm if an error occurs*/
void	handle_mutex(pthread_mutex_t *mutex, t_mutex type, t_table *table)
{
	if (LOCK == type)
		handle_mutex_error(pthread_mutex_lock(mutex), table);
	else if (UNLOCK == type)
		handle_mutex_error(pthread_mutex_unlock(mutex), table);
	else if (INIT == type)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), table);
	else if (DESTROY == type)
		handle_mutex_error(pthread_mutex_destroy(mutex), table);
	else
		error_exit("Called handle_mutex function with wrong type", table);
}

static void	handle_thread_error(int status, t_table *table)
{
	if (0 == status)
		return ;
	else if (EAGAIN == status)
		error_exit("Insufficient resources to create another thread", table);
	else if (EPERM == status)
		error_exit("Caller has no permission to thread", table);
	else if (EINVAL == status && CREATE == status)
		error_exit("Invalid settings in attr", table);
	else if (EINVAL == status)
		error_exit("Thread is not joinable", table);
	else if (ESRCH == status)
		error_exit("Thread could not be found", table);
	else if (EDEADLK == status)
		error_exit("Deadlock was detacted", table);
}

/*Function calls the corresponding pthead-function and
stops the programm if an error occurs*/
void	handle_thread(pthread_t *thread_id, void *(*foo)(void *),
			void *data, t_thread type)
{
	t_table	*table;

	if (foo == dinner_simulation)
		table = ((t_philo *)data)->table;
	else
		table = (t_table *)data;
	if (CREATE == type)
		handle_thread_error(pthread_create(thread_id, NULL, foo, data), table);
	else if (JOIN == type)
		handle_thread_error(pthread_join(*thread_id, NULL), table);
	else if (DETACH == type)
		handle_thread_error(pthread_detach(*thread_id), table);
	else
		error_exit("Called handle_thread function with wrong type", table);
}

void	*handle_malloc(size_t size, t_table *table)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		error_exit("Malloc allocation failed", table);
	return (mem);
}
