/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:44:59 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/17 19:45:46 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_table *table)
{
	long	start_eat;

	if (philo->full || simulation_finished(table))
		return ;
	handle_mutex(&philo->right_fork->fork, LOCK);
	safe_print(philo, "has taken a fork", philo->right_fork->fork_id);
	handle_mutex(&philo->left_fork->fork, LOCK);
	safe_print(philo, "has taken a fork", philo->left_fork->fork_id);
	start_eat = ft_gettime(MILLI_SEC);
	safe_print(philo, "is eating", -1);
	set_long(start_eat, &philo->last_meal, &philo->philo_mutex);
	philo->meals_eaten += 1;
	better_usleep(table->to_eat - (ft_gettime(MILLI_SEC) - start_eat), table);
	if (table->limit_meals > 0 && philo->meals_eaten >= table->limit_meals)
		set_bool(true, &philo->full, &philo->philo_mutex);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void	sleeping(t_philo *philo, t_table *table)
{
	if (simulation_finished(table))
		return ;
	safe_print(philo, "is sleeping", -1);
	better_usleep(table->to_sleep, table);
}

void	think(t_philo *philo, long usec)
{
	if (simulation_finished(philo->table))
		return ;
	safe_print(philo, "is thinking", -1);
	better_usleep(usec, philo->table);
}

//void	die(t_philo *philo, )
