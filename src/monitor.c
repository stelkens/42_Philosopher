/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:01:18 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/23 11:26:00 by tstelken         ###   ########.fr       */
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

	table = (t_table *)data;
	philo = table->philo;
	start_monitor(table);
	while (1)
	{
		i = 0;
		while (!simulation_finished(table) && i < table->num_philos)
		{
			if (ft_gettime(MILLI_SEC) - philo->last_meal >= table->to_die)
			{
				safe_print(philo, "died", -1);
				set_bool(true, &table->end_simulation, &table->read_table);
			}
			else if (get_long(table->all_full, &table->read_table) == table->num_philos)
			{
				safe_print(philo, "everyone is full", -1);
				set_bool(true, &table->end_simulation, &table->read_table);
			}
			philo = table->philo + (++i);
		}
	}
}
