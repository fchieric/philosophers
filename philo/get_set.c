/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:18:10 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 17:53:34 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_bool(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

bool    get_bool(pthread_mutex_t *mutex, bool *var)
{
	bool value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

void    set_long(pthread_mutex_t *mutex, long *var, long value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

long    get_long(pthread_mutex_t *mutex, long *var)
{
	long value;

	pthread_mutex_lock(mutex);
	value = *var;
	pthread_mutex_unlock(mutex);
	return (value);
}

void set_simulation_state(t_table *table, t_simulation_state state) {
    safe_mutex(LOCK, &table->table_mutex);
    table->sim_state = state;
    safe_mutex(UNLOCK, &table->table_mutex);
}

t_simulation_state get_simulation_state(t_table *table) {
    t_simulation_state state;
    safe_mutex(LOCK, &table->table_mutex);
    state = table->sim_state;
    safe_mutex(UNLOCK, &table->table_mutex);
    return state;
}
