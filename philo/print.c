/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:29:17 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 20:40:41 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status(t_state status, t_philo *philo)
{
    long elapsed;
    if (simulation_end(philo->table))
        return;

    safe_mutex(LOCK, &philo->table->write_mutex);

// Utilizza il timestamp globale di table->start_time
    elapsed = get_time() - philo->table->start_time;

// Debug info
    //printf("[DEBUG] Philo %d - Current time: %ld, Start time: %ld, Elapsed: %ld\n", 
      //  philo->id, get_time(), philo->table->start_time, elapsed);

    if (!simulation_end(philo->table))
    {
        if (status == FORK)
            printf("%ld %d has taken a fork\n", elapsed, philo->id);
        else if (status == EATING)
        {
            printf("%ld %d is eating (count: %ld )\n", elapsed, philo->id, philo->eat_count);
            //printf("[DEBUG] Philo %d last meal time: %ld\n", philo->id, philo->last_meal);
        }
        else if (status == SLEEPING)
            printf("%ld %d is sleeping\n", elapsed, philo->id);
        else if (status == THINKING)
            printf("%ld %d is thinking\n", elapsed, philo->id);
        else if (status == DEAD)
            printf("%ld %d died\n", elapsed, philo->id);
    }
    safe_mutex(UNLOCK, &philo->table->write_mutex);
}






/*
void    write_status(t_state status, t_philo *philo)
{
	long elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_time;
	if (philo->is_full)
		return ;
	safe_mutex(LOCK, philo->table->write_mutex);
	if (status == FORK && !simulation_end(philo->table))
	{
		print_status(status, elapsed, philo->id);
	}
	else if (status == EATING && !simulation_end(philo->table))
	{
		print_status(status, elapsed, philo->id);
		philo->eat_count++;
	}
	else if (status == SLEEPING && !simulation_end(philo->table))
	{
		print_status(status, elapsed, philo->id);
	}
	else if (status == THINKING && !simulation_end(philo->table))
	{
		print_status(status, elapsed, philo->id);
	}
	safe_mutex(UNLOCK, philo->table->write_mutex);
} 

void   print_status(t_state status, long elapsed, int id)
{	
	char buffer[100];
	int len = 0;

	len += itol(buffer + len, elapsed);
	buffer[len++] = ' ';
	len += itol(buffer + len, id);
	buffer[len++] = ' ';
	{
		if (status == FORK)
			len += ft_strcpy(buffer + len, "has taken a fork\n");
		else if (status == EATING)
			len += ft_strcpy(buffer + len, "is eating\n");
		else if (status == SLEEPING)
			len += ft_strcpy(buffer + len, "is sleeping\n");
		else if (status == THINKING)
			len += ft_strcpy(buffer + len, "is thinking\n");
	}
	write(1, buffer, len);
} */