/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:01:18 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/24 14:37:47 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_monitor(t_table *table)
{
	long	dining_philo;

	while(1)
	{
		dining_philo = get_long(&table->running_threads, &table->read_table, table);
		if (dining_philo == table->num_philos)
			break;
	}
}

static bool	philo_died(t_philo *philo)
{
	long	no_food;
	long	to_die;

	if (get_bool(&philo->full, &philo->philo_mutex, philo->table))
		return (false);
	to_die = philo->table->to_die;
	no_food = ft_gettime(MILLI_SEC) - get_long(&philo->last_meal, &philo->philo_mutex, philo->table);
	if (no_food > to_die)
		return (true);
	return (false);
}

void	*monitor_sim(void * data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *)data;
	start_monitor(table);
	while (1)
	{
		i = -1;
		while (!simulation_finished(table) && ++i < table->num_philos)
		{
			philo = table->philo + i;
			if (philo_died(philo))
			{
				safe_print(philo, "died", -1);
				set_bool(true, &table->end_simulation, &table->read_table, table);
			}
			else if (get_long(&table->all_full, &table->read_table, table) == table->num_philos)
			{
				safe_print(philo, "everyone is full", -1);
				set_bool(true, &table->end_simulation, &table->read_table, table);
			}
		}
	}
}
