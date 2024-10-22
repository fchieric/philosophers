/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:29:17 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 23:09:11 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

int itol(char *str, long num)
{
	int len = 0;
	long temp = num;

	if (num == 0)
	{
		str[len++] = '0';
		return len;
	}
	if (num < 0)
	{
		str[len++] = '-';
		num = -num;
	}
	while (temp)
{	
		temp /= 10;
		len++;
	}
	str[len] = '\0';
	while (num)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return len;
}

int ft_strcpy(char *dest, const char *src)
	{
		int len = 0;

		while (src[len])
		{
			dest[len] = src[len];
			len++;
		}

		return len;
	}