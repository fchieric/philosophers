/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:44:36 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 00:04:07 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>


# define RST "\033[0m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYN "\033[0;36m"
# define WHT "\033[0;37m"

typedef struct s_table t_table;
	
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
	
}				t_fork;


typedef struct s_philo
{
	int				id;
	long			eat_count;
	bool			is_full;
	long			last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread;
	t_table			*table;
	
}		t_philo;

typedef struct s_table
{
	long			n_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_limit; //nbr_limit_meals
	long			start_time; //start_simulation
	bool			end; //a philo has died or reached the limit
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}					t_table;


// utils.c
void error_exit(char *str);
void input_check(t_table *table);
long ft_atol(const char *str);

// init.c
void input_init(t_table *table, char **argv);


/*
#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct s_philo_table {
    int *state;
    pthread_mutex_t mutex;
    pthread_cond_t *cond;
    int n_philo;
} t_philo_table;


typedef struct s_philo
{
	int				id; // The id of the philosopher.
	int				left_fork; // The index of the left fork.
	int				right_fork; // The index of the right fork.
	int				eat_count; // The number of times the philosopher has eaten.
	pthread_t		thread; 
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				*is_dead;
	int				*is_full;
	int				*is_done;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_philo			*philos;
}					t_data;

long	ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

void	ft_usleep(int time);
void	ft_print(t_philo *philo, char *str);
void	ft_print_status(t_philo *philo, char *str);
void	ft_print_error(char *str);

void	init_philos(t_data *data);
void	ft_init_mutex(t_data *data);
void	ft_init_thread(t_data *data);
void	ft_destroy_mutex(t_data *data);
void	ft_destroy_thread(t_data *data);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_check_death(t_philo *philo);
void	*ft_routine(void *arg);
void	ft_check_full(t_data *data);

*/
#endif
