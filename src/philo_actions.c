/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:44:59 by tstelken          #+#    #+#             */
/*   Updated: 2026/02/02 13:09:44 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*if philo is not full and the simultation did't finshed,
philo takes right and left fork, when mutex is unlocked, "eats"
(usleep for the amound of time-to-eat). Each philo counts how
many times their where eating. If there is a limit of meals,
they note if they are full, and increment the counter for
how many philos are full*/
void	eat(t_philo *philo, t_table *table)
{
	long	start_eat;

	if (philo->full || simulation_finished(table))
		return ;
	handle_mutex(&philo->right_fork->fork_mx, LOCK, table);
	safe_print(philo, "has taken a fork");
	handle_mutex(&philo->left_fork->fork_mx, LOCK, table);
	safe_print(philo, "has taken a fork");
	start_eat = ft_gettime(MILLI_SEC);
	set_bool(true, &philo->eating, &philo->philo_mx, philo->table);
	safe_print(philo, "is eating");
	set_long(start_eat, &philo->last_meal, &philo->philo_mx, table);
	philo->meals_eaten += 1;
	better_usleep(table->to_eat - (ft_gettime(MILLI_SEC) - start_eat), table);
	set_bool(false, &philo->eating, &philo->philo_mx, philo->table);
	if (table->limit_meals > 0 && philo->meals_eaten >= table->limit_meals)
	{
		set_bool(true, &philo->full, &philo->philo_mx, table);
		increment_loog(&table->all_full, &table->table_mx, table);
	}
	handle_mutex(&philo->right_fork->fork_mx, UNLOCK, table);
	handle_mutex(&philo->left_fork->fork_mx, UNLOCK, table);
}

void	sleeping(t_philo *philo, t_table *table)
{
	if (simulation_finished(table))
		return ;
	safe_print(philo, "is sleeping");
	better_usleep(table->to_sleep, table);
}

void	think(t_philo *philo, long mill_sec)
{
	if (simulation_finished(philo->table))
		return ;
	safe_print(philo, "is thinking");
	better_usleep(mill_sec, philo->table);
}

