/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:47:20 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/23 10:51:33 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*checks end_simulation variable from table*/
bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->end_simulation, &table->read_table));
}