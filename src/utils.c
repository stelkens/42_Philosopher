/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:39:49 by tstelken          #+#    #+#             */
/*   Updated: 2026/02/02 13:14:32 by tstelken         ###   ########.fr       */
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
		if (get_bool(&table->philos_ready, &table->table_mx, table))
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
}

/*more precised usleep function*/
void	better_usleep(long msec, t_table *table)
{
	long	start;
	long	now;
	long	remaining;

	start = ft_gettime(MILLI_SEC);
	while (!simulation_finished(table))
	{
		now = ft_gettime(MILLI_SEC);
		remaining = msec - (now - start);
		if (remaining <= 0)
			break ;
		if (remaining > 1000 && !simulation_finished(table))
			usleep(remaining / 2);
		else
		{
			while (1 && !simulation_finished(table))
				if (ft_gettime(MILLI_SEC) - start >= msec)
					return ;
		}
	}
}

void	safe_print(t_philo *philo, char *msg)
{
	if (simulation_finished(philo->table) || philo->full)
		return ;
	handle_mutex(&philo->table->print_mutex, LOCK, philo->table);
	if (simulation_finished(philo->table) || philo->full)
	{
		handle_mutex(&philo->table->print_mutex, UNLOCK, philo->table);
		return ;
	}
	printf("%ld\t%d\t%s\n",
		ft_gettime(MILLI_SEC) - philo->table->start_time, philo->id, msg);
	handle_mutex(&philo->table->print_mutex, UNLOCK, philo->table);
}
