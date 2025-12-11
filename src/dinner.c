/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:21:21 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/11 18:06:24 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	if (!philo->id % 2)
		better_usleep(philo->table->to_eat / 2, philo->table); //think?
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			return ;
		//eat
		//sleep
		//die
		//think
	}
}

void	start_dinner(t_table *table)
{
	int		i;
	t_philo	*philo;

	//one philo dinner
	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philo[i];
		handle_thread(philo->thread_id, dinner_simulation, philo, CREATE);
	}
	table->start_time = ft_gettime(MILLI_SEC);
	set_bool(true, table->philos_ready, &table->read_table);
	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philo[i];
		handle_thread(philo->thread_id, NULL, NULL, JOIN);
	}
	//clean_up
}
