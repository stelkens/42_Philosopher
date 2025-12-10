/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:32:20 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/10 18:20:54 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	invalid_input(char **av)
{
	long	input;
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		j = 0;
		input = atol(av[i]);
		if (av[i][j] == '+' || av[i][j] == '-')
			++j;
		while (av[i][j] && av[i][j] <= '9' && av[i][j] >= '0')
			++j;
		if (av[i][j])
			error_exit("Input has to be a number");
		if (input < 0)
			error_exit("Input has to be positiv");
		if (input > INT_MAX)
			error_exit("Iput has to be smaller than INT_MAX");
		++i;
	}
}

/*if the input is valid, convert the input to microseconds*/
void	parse_input(t_table *table, char **av)
{
	invalid_input(av);
	table->num_philos = ft_atol(av[1]);
	table->to_die = ft_atol(av[2]) * 1e3;
	table->to_eat = ft_atol(av[3]) * 1e3;
	table->to_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}
