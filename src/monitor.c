/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:01:18 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/30 13:35:10 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_monitor(t_table *table)
{
	long	dining_philo;

	while(1)
	{
		dining_philo = get_long(&table->running_threads, &table->table_mx, table);
		if (dining_philo == table->num_phil)
			break ;
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
	{
		safe_print(philo, "died", -1);
		return (true);
	}
	return (false);
}

void	*monitor_sim(void *data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *)data;
	start_monitor(table);
	while (1)
	{
		i = -1;
		while (!simulation_finished(table) && ++i < table->num_phil)
		{
			philo = table->philo + i;
			if (philo_died(philo))
				set_bool(true, &table->end_sim, &table->table_mx, table);
			else if (get_long(&table->all_full, &table->table_mx, table) == table->num_phil)
			{
				print_no_tm(philo, "everyone is full");
				set_bool(true, &table->end_sim, &table->table_mx, table);
			}
		}
		if (simulation_finished(table))
			break ;
	}
	return (NULL);
}
