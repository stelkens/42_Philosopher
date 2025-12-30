/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:47:20 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/30 13:34:57 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*checks end_sim variable from table*/
bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->end_sim, &table->table_mx, table));
}

void	print_no_tm(t_philo *philo, char *msg)
{
	if (simulation_finished(philo->table))
		return ;
	handle_mutex(&philo->table->print_mutex, LOCK, philo->table);
	printf("%ld\t%s\n",
		ft_gettime(MILLI_SEC) - philo->table->start_time, msg);
	handle_mutex(&philo->table->print_mutex, UNLOCK, philo->table);
}
