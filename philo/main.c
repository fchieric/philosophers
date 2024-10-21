/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:45:46 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 00:07:03 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit("Error: Invalid number of arguments\n");
	input_init(&table, argv); // Inizializza + chiama il check input
	/*
	printf("n_philo: %ld\n", table.n_philo);
	printf("time_to_die: %ld\n", table.time_to_die);
	printf("time_to_eat: %ld\n", table.time_to_eat);
	printf("time_to_sleep: %ld\n", table.time_to_sleep);
	printf("eat_limit: %ld\n", table.eat_limit);
	*/
		//init_table(&table);
		//start_simulation(&table);
		//clean(&table);
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