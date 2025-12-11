/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:18:48 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/11 14:23:04 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_mutex type)
{
	if (0 == status)
		return ;
	if (EBUSY == status)
		error_exit("Mutix is locked");
	else if (ENOMEM == status)
		error_exit("Allocation of mutex failed");
	else if (EPERM == status)
		error_exit("Thread does not hold a lock on mutex");
	else
		error_exit("Mutex error");
}

/*Function calls the corresponding pthead_mutex-function and
stops the programm if an error occurs*/
void	handle_mutex(pthread_mutex_t *mutex, t_mutex type)
{
	if (LOCK == type)
		handle_mutex_error(pthread_mutex_lock(mutex), type);
	else if (UNLOCK == type)
		handle_mutex_error(pthread_mutex_unlock(mutex), type);
	else if (INIT == type)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), type);
	else if (DESTROY == type)
		handle_mutex_error(pthread_mutex_destroy(mutex), type);
	else
		error_exit("Wrong type for handle_mutex function");
}

static void	handle_thread_error(int status, t_mutex type)
{
	if (0 == status)
		return ;
	else if (EAGAIN == status)
		error_exit("Insufficient resources to create another thread");
	else if (EPERM == status)
		error_exit("Caller has no permission to thread");
	else if (EINVAL == status && CREATE == status)
		error_exit("Invalid settings in attr");
	else if (EINVAL == status)
		error_exit("Thread is not joinable");
	else if (ESRCH == status)
		error_exit("Thread could not be found");
	else if (EDEADLK == status)
		error_exit("Deadlock was detacted");
}

/*Function calls the corresponding pthead-function and
stops the programm if an error occurs*/
void	handle_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_thread type)
{
	if (CREATE == type)
		handle_thread_error(pthread_create(thread, NULL, foo, data), type);
	else if (JOIN == type)
		handle_thread_error(pthread_join(*thread, NULL), type);
	else if (DETACH == type)
		handle_thread_error(pthread_detach(thread), type);
	else
		error_exit("Wrong type for handle_thread function");
}

void	*handle_malloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		error_exit("Malloc allocation failed");
	return (mem);
}
