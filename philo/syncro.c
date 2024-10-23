/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:23:52 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 17:46:20 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

/*
// spinlock to synchronize the threads
void    wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		 ;
}

*/