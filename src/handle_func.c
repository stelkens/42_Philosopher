/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:18:48 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/17 18:25:20 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status)
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
		handle_mutex_error(pthread_mutex_lock(mutex));
	else if (UNLOCK == type)
		handle_mutex_error(pthread_mutex_unlock(mutex));
	else if (INIT == type)
		handle_mutex_error(pthread_mutex_init(mutex, NULL));
	else if (DESTROY == type)
		handle_mutex_error(pthread_mutex_destroy(mutex));
	else
		error_exit("Called handle_mutex function with wrong type");
}

static void	handle_thread_error(int status)
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
void	handle_thread(pthread_t *thread_id, void *(*foo)(void *),
			void *data, t_thread type)
{
	if (CREATE == type)
		handle_thread_error(pthread_create(thread_id, NULL, foo, data));
	else if (JOIN == type)
		handle_thread_error(pthread_join(*thread_id, NULL));
	else if (DETACH == type)
		handle_thread_error(pthread_detach(*thread_id));
	else
		error_exit("Called handle_thread function with wrong type");
}

void	*handle_malloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		error_exit("Malloc allocation failed");
	return (mem);
}
