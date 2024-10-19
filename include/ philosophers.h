/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    philosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchieric <fchieric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:43:29 by fchieric          #+#    #+#             */
/*   Updated: 2024/10/19 20:56:26 by fchieric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

/*
typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
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

int		ft_atoi(const char *str);
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
void	ft_init_philos(t_data *data);
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