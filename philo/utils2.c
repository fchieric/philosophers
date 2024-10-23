/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:26:51 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 19:40:05 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
    {
        perror("gettimeofday failed");
        return -1;  // Valore di errore
    }
    return tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}

void precise_usleep(long time, t_table *table)
{
    long start;
    long elapsed;
    
    start = get_time();
    while (!simulation_end(table))
    {
        elapsed = get_time() - start;
        if (elapsed >= time)
            break;
        
        if (time - elapsed > 1000)
            usleep(500);
        else
            usleep(100);
    }
}

