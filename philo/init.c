/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 04:10:53 by fabi              #+#    #+#             */
/*   Updated: 2024/10/21 21:57:13 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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