/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:32:20 by tstelken          #+#    #+#             */
/*   Updated: 2025/12/30 13:10:16 by tstelken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*test if the imput only contains positiv numbers
in the range of 0 to INT_MAX*/
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
			error_exit("Input has to be a number", NULL);
		if (input < 0)
			error_exit("Input has to be positiv", NULL);
		if (input > INT_MAX)
			error_exit("Input has to be smaller than INT_MAX", NULL);
		++i;
	}
}

/*if the input is valid, convert the input to microseconds
and add it to the struct.*/
void	parse_input(t_table *table, char **av)
{
	invalid_input(av);
	memset(table, 0, sizeof(t_table));
	table->num_phil = ft_atol(av[1]);
	table->to_die = ft_atol(av[2]);
	table->to_eat = ft_atol(av[3]);
	table->to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		table->limit_meals = ft_atol(av[5]);
		table->all_full = 0;
	}
	else
		table->limit_meals = -1;
	if (table->limit_meals == 0)
		exit(EXIT_SUCCESS);
}

/*set fork-mutex and gives philosophers pointer to left 
and right fork. If there is just one philo, they get only
a right fork*/
static void	set_fork(t_philo *philo, t_fork *forks, int i)
{
	int		j;
	long	num_philo;

	num_philo = philo->table->num_phil;
	if (i == 0)
	{
		j = -1;
		while (++j < num_philo)
		{
			handle_mutex(&forks[j].fork_mx, INIT, philo->table);
			forks[j].fork_id = j;
		}
	}
	philo->right_fork = &forks[i];
	if (num_philo > 1)
		philo->left_fork = &forks[(i + 1) % num_philo];
}

/*set table variables and allocs memory for the philosophers
and the forks. Sets the forks*/
void	set_table(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	// table->dead_philo = 0;
	// table->end_sim = false;
	table->philo = handle_malloc(table->num_phil * sizeof(t_philo), table);
	table->forks = handle_malloc(table->num_phil * sizeof(t_fork), table);
	// table->philos_ready = false;
	// table->running_threads = 0;
	// table->all_full = 0;
	handle_mutex(&table->table_mx, INIT, table);
	handle_mutex(&table->print_mutex, INIT, table);
	while (++i < table->num_phil)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->full = false;
		philo->table = table;
		handle_mutex(&philo->philo_mutex, INIT, table);
		set_fork(philo, table->forks, i);
	}
}
