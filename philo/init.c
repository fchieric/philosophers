/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 04:10:53 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 03:01:33 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int philo_num;

	philo_num = philo->table->n_philo;
	philo->right_fork = &forks[i];
	philo->left_fork = &forks[(i + 1) % philo_num];
}

static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->n_philo)
	{
		philo = &table->philos[i];  // Puntiamo al filosofo corrente
		philo->id = i + 1;
		philo->eat_count = 0;
		philo->is_full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);  // Assegniamo le forchette
		i++;
	}
}

void	init_table(t_table *table)
{
	int i;

	i = 0;
	table->end = false;
	table->philos = safe_malloc(table->n_philo * sizeof(t_philo));
	table->forks = safe_malloc(table->n_philo * sizeof(t_fork));

	// Inizializzazione dei mutex per le forchette
	while (i < table->n_philo)
	{
		safe_mutex(INIT, &table->forks[i].mutex);
		table->forks[i].fork_id = i;
		i++;
	}

	// Inizializzazione dei filosofi
	init_philo(table);
}

/*
static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int philo_num;

	philo_num = philo->table->n_philo;
	philo->right_fork = &forks[i];
	philo->left_fork = &forks[(i + 1) % philo_num];
}


static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->n_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->eat_count = 0;
		philo->is_full = false;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}


void	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->end = false;
	table->philos = safe_malloc(table->n_philo * sizeof(t_philo));
	table->forks = safe_malloc(table->n_philo * sizeof(t_fork));
	while (i < table->n_philo)
	{
		safe_mutex(INIT, &table->forks[i].mutex);
		table->forks[i].fork_id = i;
		i++;
	}
	init_philo(table);
}
*/


void	input_check(t_table *table)
{
	if (table->n_philo == INT_MAX)
	{
		error_exit("Error: Invalid number of philosophers 🥶\n");
	}
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		error_exit("Error: Time values must be at least 60 ms 🥺\n");
	}
	if (table->time_to_die > INT_MAX || table->time_to_eat > INT_MAX
		|| table->time_to_sleep > INT_MAX)
	{
			error_exit("Error: Time values must be comprised between 0 and INT_MAX 🥺\n");
	}
}

void	input_init(t_table *table, char **argv)
{
	table->n_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->eat_limit = -1;
	if (argv[5])
	{
		table->eat_limit = ft_atol(argv[5]);
	}
	if (table->time_to_die != LONG_MAX && table->time_to_eat != LONG_MAX && table->time_to_sleep != LONG_MAX)
	{
		table->time_to_die = ft_atol(argv[2]) * 1000;
		table->time_to_eat = ft_atol(argv[3]) * 1000;
		table->time_to_sleep = ft_atol(argv[4]) * 1000;
	}
	input_check(table);
}
