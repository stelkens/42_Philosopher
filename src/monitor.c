/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:01:18 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/22 11:12:13 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_monitor(t_table *table)
{
	long	dining_philo;

	while(1)
	{
		dining_philo = get_long(table->running_threads, &table->read_table);
		if (dining_philo == table->num_philos)
			break;
	}
}

void	*monitor_sim(void * data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;
	long	time_to_die;

	table = (t_table *)data;
	start_monitor(table);
	while (1)
	{
		
	}
}
