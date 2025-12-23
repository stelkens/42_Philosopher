/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:38:39 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/23 10:53:34 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*returns the value of a long variable from the table*/
long	get_long(long *src, pthread_mutex_t *mutex)
{
	long	var;

	handle_mutex(mutex, LOCK);
	var = *src;
	handle_mutex(mutex, UNLOCK);
	return (var);
}

/*sets a long variable from the table to "value"*/
void	set_long(long value, long *dest, pthread_mutex_t *mutex)
{
	handle_mutex(mutex, LOCK);
	*dest = value;
	handle_mutex(mutex, UNLOCK);
}

/*returns the value of a long variable from the table*/
bool	get_bool(bool *src, pthread_mutex_t *mutex)
{
	bool	var;

	handle_mutex(mutex, LOCK);
	var = *src;
	handle_mutex(mutex, UNLOCK);
	return (var);
}

/*sets a long variable from the table to "value"*/
void	set_bool(bool value, bool *dest, pthread_mutex_t *mutex)
{
	handle_mutex(mutex, LOCK);
	*dest = value;
	handle_mutex(mutex, UNLOCK);
}

void	increment_loog(long *dest, pthread_mutex_t *mutex)
{
	handle_mutex(mutex, LOCK);
	(*dest) += 1;
	handle_mutex(mutex, UNLOCK);
}
