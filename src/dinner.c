/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:21:21 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/17 19:57:38 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(ft_gettime(MILLI_SEC), &philo->last_meal, &philo->philo_mutex);
	//if one philo dinner_for_one
	// signal threat is running
	if (philo->id % 2 < 1)
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

void	start_dinner(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philo[i];
		handle_thread(&philo->thread_id, dinner_simulation, philo, CREATE);
	}
	//set monitor: waits until all threats are running
	table->start_time = ft_gettime(MILLI_SEC);
	set_bool(true, &table->philos_ready, &table->read_table);
	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philo[i];
		handle_thread(&philo->thread_id, NULL, NULL, JOIN);
	}
	set_bool(true, &table->end_simulation, &table->read_table);
	//thread join monitor
	
	//clean_up > unlock all locks (halgrind check)
	//lock in the print fuction
}
