/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:49:38 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 03:05:58 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t current_time_in_ms(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}


void *philo_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    printf("Philosopher %d started\n", philo->id);

    while (!philo->table->end)
    {
        printf("Philosopher %d is thinking\n", philo->id);
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->right_fork->mutex);
            pthread_mutex_lock(&philo->left_fork->mutex);

        }
        else
        {
            pthread_mutex_lock(&philo->right_fork->mutex);
            pthread_mutex_lock(&philo->left_fork->mutex);
        }
        printf("Philosopher %d is eating\n", philo->id);
        philo->last_meal = current_time_in_ms();
        philo->eat_count++;
        usleep(philo->table->time_to_eat);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        pthread_mutex_unlock(&philo->left_fork->mutex);

        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(philo->table->time_to_sleep);
    }
    return (NULL);
}


void start_simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->n_philo)
	{
		// Creazione dei thread per i filosofi
		safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		// Attesa che i filosofi finiscano
		safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
		i++;
	}
}
