/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 04:10:53 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 00:36:27 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	//int	i;

	//i = 0;
	table->end = false;
	table->philos = safe_malloc(table->n_philo * sizeof(t_philo));
}

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

/*
t_philo_table* init_table(int n_philo)
{
	t_philo_table *table = malloc(sizeof(t_philo_table));
	table->n_philo = n_philo;
	table->state = malloc(n_philo * sizeof(int));
	table->cond = malloc(n_philo * sizeof(pthread_cond_t));
	
	pthread_mutex_init(&table->mutex, NULL);
	for (int i = 0; i < n_philo; i++) {
		table->state[i] = THINKING;
		pthread_cond_init(&table->cond[i], NULL);
	}
	
	return table;
}
*/


/*
// Initializes the philos array with the necessary values.
// The id is set to the index + 1.
// The left fork is set to the index.
// The right fork is set to the index + 1 modulo the philo_count.
// The eat_count is set to 0.
// The forks is set to the forks array.
// The print is set to the print mutex.
// The death is set to the death mutex.
void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].eat_count = 0;
		data->philos[i].forks = data->forks;
		data->philos[i].print = &data->print;
		data->philos[i].death = &data->death;
		i++;
	}
}
*/