/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:45:46 by fabi              #+#    #+#             */
/*   Updated: 2024/10/21 23:52:53 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*
int	arg_check(int argc, char **argv)
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
	if (ft_atol(argv[1]) > INT_MAX || ft_atol(argv[2]) > INT_MAX
		|| ft_atol(argv[3]) > INT_MAX || ft_atol(argv[4]) > INT_MAX)
	{
		perror("Error: Arguments must be less than INT_MAX\n");
		exit(1);
	}
	return (0);
} */

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

void error_exit(char *message)
{
    write(2, message, ft_strlen(message));
    exit(1);
}

/* uso il long max per gestirmi gli errori se  negativo o se non è un numero */
void	input_check(t_table *table)
{
	if (table->n_philo == LONG_MAX || table->n_philo == INT_MAX)
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

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit("Error: Invalid number of arguments\n");
	input_init(&table, argv); // Inizializza + chiama il check input
	printf("n_philo: %ld\n", table.n_philo);
	printf("time_to_die: %ld\n", table.time_to_die);
	printf("time_to_eat: %ld\n", table.time_to_eat);
	printf("time_to_sleep: %ld\n", table.time_to_sleep);
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