/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:01:18 by tstelken          #+#    #+#             */
/*   Updated: 2026/02/02 13:01:18 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_monitor(t_table *table)
{
	long	dining_philo;

	while (1)
	{
		dining_philo = get_long(&table->running_thrds, &table->table_mx, table);
		if (dining_philo == table->num_phil)
			break ;
	}
}

/*if philo is not full and philo is not eating at the moment,
checks if time since last meal is larger then time-to-die.
Prints a dead notification.*/
static bool	philo_died(t_philo *philo)
{
	long	no_food;
	long	to_die;

	if (get_bool(&philo->full, &philo->philo_mx, philo->table))
		return (false);
	to_die = philo->table->to_die;
	handle_mutex(&philo->philo_mx, LOCK, philo->table);
	no_food = ft_gettime(MILLI_SEC) - philo->last_meal;
	if (no_food > to_die && !philo->eating)
	{
		handle_mutex(&philo->table->print_mutex, LOCK, philo->table);
		printf("%ld\t%d\t%s\n",
			ft_gettime(MILLI_SEC) - philo->table->start_time,
			philo->id, "died");
		set_bool(true, &philo->table->end_sim,
			&philo->table->table_mx, philo->table);
		usleep(10);
		handle_mutex(&philo->table->print_mutex, UNLOCK, philo->table);
		handle_mutex(&philo->philo_mx, UNLOCK, philo->table);
		return (true);
	}
	handle_mutex(&philo->philo_mx, UNLOCK, philo->table);
	return (false);
}

/*monitor checks if a philo is dead and if everyone is full.
Stops the simulation if either is true*/
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
			else if (get_long(&table->all_full, &table->table_mx,
					table) == table->num_phil)
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
