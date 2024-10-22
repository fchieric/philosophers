/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:02:53 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 23:09:34 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool try_take_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	if (philo->table->end)
		return false;

	// Determina l'ordine delle forchette per evitare deadlock
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}

	safe_mutex(LOCK, &first_fork->mutex);
	print_status(philo->table, philo->id, FORK);
	safe_mutex(LOCK, &second_fork->mutex);
	print_status(philo->table, philo->id, FORK);

	return true;
}

void eating_phase(t_philo *philo)
{
	size_t start_time;

	safe_mutex(LOCK, &philo->table->death);
	philo->last_meal = current_time_in_ms();
	philo->eat_count++;
	if (philo->table->eat_limit != -1 && philo->eat_count >= philo->table->eat_limit)
	{
		philo->is_full = true;
	}
	safe_mutex(UNLOCK, &philo->table->death);

	print_status(philo->table, philo->id, EATING);
	
	start_time = current_time_in_ms();
	while ((current_time_in_ms() - start_time) < (size_t)philo->table->time_to_eat)
		usleep(500);
}

// routine dei philos
void *philo_life(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	// set last meal time
	while (!simulation_end(philo->table))
	{
		if (philo->is_full)
			break ;
		//eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		//think(philo);
		break ;
	}
	return (NULL);
}

// start the program after the input check
void start_simulation(t_table *table)
{
	int i;

	i = 0;
	if (table->eat_limit == 0)
		return ;
	else if (table->n_philo == 1)
		return ;//toDO A FUNTION
	else
	{
		while (i < table->n_philo)
		{
			safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
			i++;
		}
	}
	table->start_time = get_time(MILLISECOND);
	set_bool(table->table_mutex, &table->all_threads_ready, true);
	while (i < table->n_philo)
	{
		safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
		i++;
	}
	// if we reach here all philos are full
}

/*
void start_simulation(t_table *table)
{
	pthread_t monitor;
	int i;

	table->start_time = current_time_in_ms();
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
		i++;
	}
	safe_thread(&monitor, monitor_philosophers, table, CREATE);
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
		i++;
	}
	safe_thread(&monitor, NULL, NULL, JOIN);
}

*/