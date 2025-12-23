/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:17:12 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/23 11:35:07 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *error_msg)
{
	printf("Error: %s\n", error_msg);
	exit (EXIT_FAILURE);
}

static void	clean_up(t_table *table)
{
	//hier weiter
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments");
	parse_input(&table, argv);
	set_table(&table);
	start_dinner(&table);
	clean_up(&table);
	//clean_function:destroy all mutex; free forks and philo
	//clean_up > unlock all locks (halgrind check)
	return (0);
}
//min 1.36
