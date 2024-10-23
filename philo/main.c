/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:45:46 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 20:43:25 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void update_death(t_philo *philo, long current_time)
{
    long last_meal;

    // Blocca il mutex del filosofo per leggere il suo ultimo pasto
    safe_mutex(LOCK, &philo->mutex);
    last_meal = philo->last_meal;
    safe_mutex(UNLOCK, &philo->mutex);
    
    // Verifica se il filosofo è morto
    if (current_time - last_meal > philo->table->time_to_die)
    {
        //printf("[DEBUG] Philosopher %d died. Current time: %ld, Last meal: %ld, Time to die: %ld\n",
          //     philo->id, current_time, last_meal, philo->table->time_to_die);
        write_status(DEAD, philo);
        set_simulation_state(philo->table, END);
    }
}


void *death_checker(void *arg)
{
    t_table *table = (t_table *)arg;
    long current_time;
    bool dead_found = false;

    //printf("[DEBUG] Death checker started\n");

    // Aspetta che tutti i thread siano pronti
    while (!get_bool(&table->start_mutex, &table->all_threads_ready)) {
        if (get_simulation_state(table) == END) {
            //printf("[DEBUG] Death checker ending (simulation ended before start)\n");
            return NULL;
        }
        precise_usleep(1000, table);
    }

    while (get_simulation_state(table) == RUNNING && !dead_found)
    {
        for (int i = 0; i < table->n_philo && !dead_found; i++)
        {
            current_time = get_time();
            safe_mutex(LOCK, &table->philos[i].mutex);
            if (current_time - table->philos[i].last_meal > table->time_to_die / 1000)
            {
                //printf("[DEBUG] Philosopher %d died at time %ld (last meal: %ld)\n",
                   //    i + 1, current_time, table->philos[i].last_meal);
                write_status(DEAD, &table->philos[i]);
                set_simulation_state(table, END);
                dead_found = true;
            }
            safe_mutex(UNLOCK, &table->philos[i].mutex);
        }
        precise_usleep(1000, table); // Check ogni millisecondo
    }

    //printf("[DEBUG] Death checker ending\n");
    return NULL;
}





bool simulation_end(t_table *table)
{
    return get_bool(&table->table_mutex, &table->end);
}


void clean_up(t_table *table)
{
    int i;

    // Distruggere i mutex dei filosofi
    for (i = 0; i < table->n_philo; i++)
    {
        pthread_mutex_destroy(&table->philos[i].mutex);
    }

    // Distruggere i mutex delle forchette
    for (i = 0; i < table->n_philo; i++)
    {
        pthread_mutex_destroy(&table->forks[i].mutex);
    }

    // Distruggere i mutex della tavola
    pthread_mutex_destroy(&table->table_mutex);
    pthread_mutex_destroy(&table->write_mutex);
    pthread_mutex_destroy(&table->start_mutex);  // Distruggi il mutex `start_mutex`

    // Liberare la memoria allocata
    free(table->philos);
    free(table->forks);
}



int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit("Error: Invalid number of arguments\n");
	input_init(&table, argv); // Inizializza + chiama il check input
	init_table(&table);
	start_simulation(&table);
	clean_up(&table);
	return (0);
}

/*
void argv_parser(int argc, char **argv)
{

	if (argc < 5 || argc > 6)
	{
		perror("Error: Invalid number of arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1], "0", 1) == 0 || ft_atoi(argv[1]) < 1)
	{
		perror("Error: Number of philosophers must be greater than 0\n");
		exit(1);
	}
	if (ft_strncmp(argv[2], "0", 1) == 0 || ft_atoi(argv[2]) < 60)
	{
		perror("Error: Time to die must be greater than 59\n");
		exit(1);
	}
}


int	main(int argc, char **argv)
{
	t_data	data;
	
	argv_parser(argc, argv);
	data_init(data, argv);
	
	return (0);
}

int main(int argc, char **argv) {
	int num_philo = 5;
	t_philo_table *table = init_table(table->n_philo);
	pthread_t threads[num_philo];
	philosopher_args args[num_philo];

	for (int i = 0; i < num_philo; i++) {
		args[i].table = table;
		args[i].id = i;
		pthread_create(&threads[i], NULL, philosopher, &args[i]);
	}

	for (int i = 0; i < num_philo; i++) {
		pthread_join(threads[i], NULL);
	}

	// Clean up (we could also move this to a separate function)
	pthread_mutex_destroy(&table->mutex);
	for (int i = 0; i < num_philo; i++) {
		pthread_cond_destroy(&table->cond[i]);
	}
	free(table->state);
	free(table->cond);
	free(table);

	return 0;
}
*/