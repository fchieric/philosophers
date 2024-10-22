/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:26:51 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 22:58:23 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(t_timecd code)
{
    struct timeval  tv;
    long            time;
    
	if (gettimeofday(&tv, NULL) == -1)
		error_exit("Error: gettimeofday() failed 🥵\n");
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (code == SECOND)
        return (tv.tv_sec);
    else if (code == MICROSECOND)
        return (tv.tv_usec);
    return (time);
}

void    precise_usleep(long time, t_table *table)
{
    long    start;
	long	elapsed;
	long	remaining;
    
    start = get_time(MICROSECOND);
    while (get_time(MICROSECOND) - start < time)
    {
        if (simulation_end(table))
			break ;
		elapsed = time - (get_time(MICROSECOND) - start);
		remaining = time - elapsed;
		// if more than 1 millisecond remaining
		if (remaining > 1e3)
			usleep(time / 2);
		else
		{
			while (get_time(MICROSECOND) - start < time)
				;
		}
    }
}

