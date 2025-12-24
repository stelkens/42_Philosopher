/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:17:12 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/24 14:25:35 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *error_msg, t_table *table)
{
	if (!table)
	{
		printf("Error: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	if (table)
	{
		handle_mutex(&table->print_mutex, LOCK, table);
		printf("Error: %s\n", error_msg);
		handle_mutex(&table->print_mutex, UNLOCK, table);
		set_bool(true, &table->end_simulation, &table->read_table, table);
		table->error = 1;
	}
	
}

static void	clean_up(t_table *table)
{
	int	i;
	t_philo	*philo;
	t_fork	*fork;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = table->philo +i;
		handle_mutex(&philo->philo_mutex, DESTROY, table);
		free(philo);
	}
	i = -1;
	while (++i < table->num_philos)
	{
		fork = table->forks + i;
		handle_mutex(&fork->fork, DESTROY, table);
		free(fork);
	}
	handle_mutex(&table->read_table, DESTROY, table);
	handle_mutex(&table->print_mutex, DESTROY, table);
	if (table->error)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments", NULL);
	parse_input(&table, argv);
	set_table(&table);
	start_dinner(&table);
	clean_up(&table);
	//clean_function:destroy all mutex; free forks and philo
	//clean_up > unlock all locks (halgrind check)
	return (0);
}
//min 2.07 think verbessern?
