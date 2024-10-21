/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:35:45 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 00:36:11 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *safe_malloc(size_t size)
{
	void *ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		error_exit("Error: Malloc failed :(\n");
	}
	return (ret);
}

void safe_mutex(t_opcode opcode, pthread_mutex_t *mutex)
{
	if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			error_exit("Error: Mutex lock failed :(\n");
    }
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
		{
			error_exit("Error: Mutex unlock failed :(\n");
		}
	}
	else if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			error_exit("Error: Mutex init failed :(\n");
		}
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
		{
			error_exit("Error: Mutex destroy failed :(\n");
		}
	}
}