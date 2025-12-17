/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:39:49 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/17 19:24:03 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	size_t	i;
	long	num;
	long	neg;

	i = 0;
	num = 0;
	neg = 0;
	if (!nptr || !*nptr)
		return (num);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	if (neg)
		return (-num);
	return (num);
}

void	wait_all_philos(t_table *table)
{
	while (1)
	{
		if (get_bool(&table->philos_ready, &table->read_table))
			break ;
	}
}

/*gets the time in mil-sec or micro-sec.
gettimeofday puts seconds (tv_sec) and miro-sec (usec) in struct.
1e3 = 1000; 1e6 = 1000.000*/
long	ft_gettime(t_time type)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (MILLI_SEC == type)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICRO_SEC)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
		error_exit("Called ft_gettime with wrong type");
	return (1312);
}

void	better_usleep(long msec, t_table *table)
{
	long	start;
	long	tm_past;
	long	remaining;

	start = ft_gettime(MILLI_SEC);
	while (ft_gettime(MILLI_SEC) - start < msec && !simulation_finished(table))
	{
		tm_past = ft_gettime(MILLI_SEC) - start;
		remaining = msec - tm_past;
		if (ft_gettime(MILLI_SEC) - start < remaining && remaining > 1000)
			usleep(remaining / 2);
		else
		{
			while (1)
				if (ft_gettime(MILLI_SEC) - start == msec)
					return ;
		}
	}
}

void	safe_print(t_philo *philo, char *msg, int fork_id)
{
	if (simulation_finished(philo->table) || philo->full)
		return ;
	handle_mutex(&philo->table->print_mutex, LOCK);
	printf("%ld\t%d\t%s [fork id %d]\n",
		ft_gettime(MILLI_SEC) - philo->table->start_time, philo->id, msg, fork_id);
	handle_mutex(&philo->table->print_mutex, UNLOCK);
}
