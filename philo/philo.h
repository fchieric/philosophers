/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:44:36 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 20:24:49 by fabi             ###   ########.fr       */
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
# include <errno.h>

#define MAX_BACKOFF 1000000  // Massimo tempo di backoff in microsecondi

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DEAD,
}		t_state;

typedef enum e_simulation_state {
    RUNNING,
    END
} t_simulation_state;


typedef struct s_table t_table;
	
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex; //fork
	
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
	pthread_mutex_t	mutex;
	
}		t_philo;

typedef struct s_table {
    long n_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long eat_limit;
    long start_time;
    t_simulation_state sim_state;  // Stato della simulazione (RUNNING o END)
    bool all_threads_ready;
	bool end;
    t_philo *philos;
    t_fork *forks;
    pthread_mutex_t print;
    pthread_mutex_t death;
    pthread_mutex_t table_mutex;
    pthread_mutex_t write_mutex;
    pthread_t death_checker;
    pthread_mutex_t start_mutex;
    int ready_count;
} t_table;


// main.c
void *safe_malloc(size_t size);
void *death_checker(void *arg);

// utils.c
void error_exit(char *str);
void input_check(t_table *table);
long ft_atol(const char *str);

// init.c
void input_init(t_table *table, char **argv);
void init_table(t_table *table);

void *philo_life(void *arg);

// safe_funcs.c
void safe_thread(pthread_t *thread, void *(*func)(void *), void *arg, t_opcode op);

// philo.c
void start_simulation(t_table *table);
size_t current_time_in_ms(void);

// clean_up.c
void clean_up(t_table *table);

void philo_sleep(t_philo *philo);

// get_set.c
void set_bool(pthread_mutex_t *mutex, bool *var, bool value);
bool get_bool(pthread_mutex_t *mutex, bool *var);
void set_long(pthread_mutex_t *mutex, long *var, long value);
long get_long(pthread_mutex_t *mutex, long *var);
bool simulation_end(t_table *table);

//void wait_all_threads(t_table *table);
long get_time(void);

void precise_usleep(long time, t_table *table);
void write_status(t_state status, t_philo *philo);


int safe_mutex(t_opcode opcode, pthread_mutex_t *mutex);
void write_status(t_state status, t_philo *philo);
//void wait_all_threads(t_table *table);
void eat(t_philo *philo);
void think(t_philo *philo);
t_fork *get_first_fork(t_philo *philo);
t_fork *get_second_fork(t_philo *philo);

void mutex_error(int status, t_opcode opcode);

void set_simulation_state(t_table *table, t_simulation_state state);
t_simulation_state get_simulation_state(t_table *table);

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
