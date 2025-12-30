/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:47:20 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/30 12:48:22 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*checks end_sim variable from table*/
bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->end_sim, &table->table_mx, table));
}