/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:21:21 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/30 12:48:32 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *data);

void	start_dinner(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_phil)
	{
		philo = &table->philo[i];
		handle_thread(&philo->thread_id, dinner_simulation, (void *)philo, CREATE);
	}
	handle_thread(&table->monitor, monitor_sim, (void *)table, CREATE);
	table->start_time = ft_gettime(MILLI_SEC);
	set_bool(true, &table->philos_ready, &table->table_mx, table);
	i = -1;
	while (++i < table->num_phil)
	{
		philo = &table->philo[i];
		handle_thread(&philo->thread_id, NULL, NULL, JOIN);
	}
	set_bool(true, &table->end_sim, &table->table_mx, table);
	safe_print(philo, "everyone is full", -1);
	handle_thread(&table->monitor, NULL, NULL, JOIN);
}

static void	dinner_for_one(t_philo *philo)
{
	safe_print(philo, "has taken a fork", philo->right_fork->fork_id);
	better_usleep(philo->table->to_die + 100, philo->table);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(ft_gettime(MILLI_SEC), &philo->last_meal, &philo->philo_mutex, philo->table);
	increment_loog(&philo->table->running_threads, &philo->table->table_mx, philo->table);
	if (philo->table->num_phil == 1)
		dinner_for_one(philo);
	if (philo->id % 2 < 1 && !simulation_finished(philo->table))
		think(philo, philo->table->to_eat / 2);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			return (NULL);
		eat(philo, philo->table);
		sleeping(philo, philo->table);
		think(philo, 1);
	}
	return (NULL);
}


