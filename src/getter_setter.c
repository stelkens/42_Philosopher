/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:38:39 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/24 14:23:53 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*returns the value of a long variable from the table*/
long	get_long(long *src, pthread_mutex_t *mutex, t_table *table)
{
	long	var;

	handle_mutex(mutex, LOCK, table);
	var = *src;
	handle_mutex(mutex, UNLOCK, table);
	return (var);
}

/*sets a long variable from the table to "value"*/
void	set_long(long value, long *dest, pthread_mutex_t *mutex, t_table *table)
{
	handle_mutex(mutex, LOCK, table);
	*dest = value;
	handle_mutex(mutex, UNLOCK, table);
}

/*returns the value of a long variable from the table*/
bool	get_bool(bool *src, pthread_mutex_t *mutex, t_table *table)
{
	bool	var;

	handle_mutex(mutex, LOCK, table);
	var = *src;
	handle_mutex(mutex, UNLOCK, table);
	return (var);
}

/*sets a long variable from the table to "value"*/
void	set_bool(bool value, bool *dest, pthread_mutex_t *mutex, t_table *table)
{
	handle_mutex(mutex, LOCK, table);
	*dest = value;
	handle_mutex(mutex, UNLOCK, table);
}

void	increment_loog(long *dest, pthread_mutex_t *mutex, t_table *table)
{
	handle_mutex(mutex, LOCK, table);
	(*dest) += 1;
	handle_mutex(mutex, UNLOCK, table);
}
