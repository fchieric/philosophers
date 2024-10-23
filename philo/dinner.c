/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:02:53 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 15:51:14 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void take_forks(t_philo *philo)
{
    if (!philo || simulation_end(philo->table))
        return;
    
    t_fork *first_fork;
    t_fork *second_fork;
    
    // Evita deadlock facendo prendere le forchette in ordine diverso
    // ai filosofi pari e dispari
    if (philo->id % 2 == 0)
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    else
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    
    safe_mutex(LOCK, &first_fork->mutex);
    write_status(FORK, philo);
    safe_mutex(LOCK, &second_fork->mutex);
    write_status(FORK, philo);
}

void release_forks(t_philo *philo)
{
    if (!philo)
        return;
        
    safe_mutex(UNLOCK, &philo->right_fork->mutex);
    safe_mutex(UNLOCK, &philo->left_fork->mutex);
}

void eat(t_philo *philo) {
    if (!philo || simulation_end(philo->table))
        return;

    take_forks(philo);
    
    safe_mutex(LOCK, &philo->mutex);
    philo->last_meal = get_time(); // Aggiorna `last_meal` mentre il mutex è bloccato
    philo->eat_count++;
    if (philo->table->eat_limit > 0 && 
        philo->eat_count >= philo->table->eat_limit)
        philo->is_full = true;
    safe_mutex(UNLOCK, &philo->mutex);
    
    write_status(EATING, philo);
    precise_usleep(philo->table->time_to_eat, philo->table);
    
    release_forks(philo);
}


void think(t_philo *philo) {
    write_status(THINKING, philo);
}

void *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!philo)
        return (NULL);

    // Attendi che `all_threads_ready` sia impostato a true
    while (!get_bool(&philo->table->start_mutex, &philo->table->all_threads_ready))
        precise_usleep(100);

    // Offset per filosofi pari per evitare deadlock iniziale
    if (philo->id % 2 == 0)
        precise_usleep(100, philo->table);  // Aumentato a 2ms per dare più margine

    // Loop della vita del filosofo
    while (!simulation_end(philo->table) && !philo->is_full)
    {
        eat(philo);
        if (!simulation_end(philo->table))
        {
            write_status(SLEEPING, philo);
            precise_usleep(philo->table->time_to_sleep, philo->table);
        }
        if (!simulation_end(philo->table))
        {
            write_status(THINKING, philo);
        }
    }
    return (NULL);
}


// start the program after the input check
void log_simulation_start(t_table *table)
{
    printf("Start time initialized: %ld\n", table->start_time);
}

void start_simulation(t_table *table)
{
    int i;
    pthread_t death_thread;

    if (!table || table->n_philo <= 0)
        return;

    // Crea tutti i thread dei filosofi
    i = 0;
    while (i < table->n_philo)
    {
        safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
        i++;
    }

    // Imposta il tempo di inizio dopo aver creato tutti i filosofi
    safe_mutex(LOCK, &table->start_mutex);
    table->start_time = get_time();
    log_simulation_start(table);  // Log dell'inizio della simulazione
    table->all_threads_ready = true;  // Segnala che tutti i thread sono pronti
    safe_mutex(UNLOCK, &table->start_mutex);

    // Crea il thread per il controllo della morte
    safe_thread(&death_thread, death_checker, table, CREATE);

    // Attendi la fine di tutti i thread
    i = 0;
    while (i < table->n_philo)
    {
        safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
        i++;
    }
    safe_thread(&death_thread, NULL, NULL, JOIN);
}





/*
t_fork *get_first_fork(t_philo *philo)
{
    if (philo->left_fork->fork_id < philo->right_fork->fork_id)
    {
        return philo->left_fork;
    }
    return philo->right_fork;
}

t_fork *get_second_fork(t_philo *philo)
{
    if (philo->left_fork->fork_id > philo->right_fork->fork_id)
    {
        return philo->left_fork;
    }
    return philo->right_fork;
}


void both_forks(t_philo *philo)
{
    t_fork *first_fork;
    t_fork *second_fork;

    // Alterna l'ordine di presa delle forchette in base all'ID del filosofo
    if (philo->id % 2 == 0)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }

    if (simulation_end(philo->table))
        return;

    // Blocca il primo fork
    safe_mutex(LOCK, &first_fork->mutex);
    write_status(FORK, philo);

    // Se c'è un solo filosofo, aspetta finché non muore
    if (philo->table->n_philo == 1)
    {
        precise_usleep(philo->table->time_to_die, philo->table);
        safe_mutex(UNLOCK, &first_fork->mutex);
        return;
    }

    // Prova a bloccare il secondo fork
    safe_mutex(LOCK, &second_fork->mutex);
    write_status(FORK, philo);
}






void eat(t_philo *philo)
{
    t_fork *first_fork;
    t_fork *second_fork;

    // Alterna l'ordine di presa delle forchette in base all'ID del filosofo
    if (philo->id % 2 == 0)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }

    if (!both_forks(philo))
        return;

    write_status(EATING, philo);
    set_long(&philo->mutex, &philo->last_meal, get_time());
    philo->eat_count++;
    precise_usleep(philo->table->time_to_eat, philo->table);

    if (philo->table->eat_limit > 0 && philo->eat_count >= philo->table->eat_limit)
        set_bool(&philo->mutex, &philo->is_full, true);

    // Rilascia le forchette
    safe_mutex(UNLOCK, &second_fork->mutex);
    safe_mutex(UNLOCK, &first_fork->mutex);
}






void think(t_philo *philo) {
    write_status(THINKING, philo);
}

void *philo_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Log per vedere quando il filosofo inizia la propria vita
    printf("Philosopher %d starting life.\n", philo->id);

    // Attendi che `all_threads_ready` sia impostato a true
    while (1)
    {
        safe_mutex(LOCK, &philo->table->start_mutex);
        if (philo->table->all_threads_ready)
        {
            safe_mutex(UNLOCK, &philo->table->start_mutex);
            break;  // Se `all_threads_ready` è true, esci dal ciclo di attesa
        }
        safe_mutex(UNLOCK, &philo->table->start_mutex);
        usleep(100);  // Breve pausa per non sovraccaricare la CPU
    }

    // Log per verificare che il filosofo abbia ricevuto il segnale di start
    printf("Philosopher %d received start signal.\n", philo->id);

    // Aggiungi un piccolo delay per i filosofi pari per evitare deadlock
    if (philo->id % 2 == 0)
        precise_usleep(1000, philo->table);  // 1ms delay

    // Loop principale della vita del filosofo
    while (!simulation_end(philo->table) && !philo->is_full)
    {
        printf("Philosopher %d attempting to take forks.\n", philo->id);
        if (!both_forks(philo))
            break;
        eat(philo);
        write_status(SLEEPING, philo);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        write_status(THINKING, philo);
    }
    return NULL;
}





// start the program after the input check
void start_simulation(t_table *table)
{
    int i = 0;

    if (table->eat_limit == 0)
        return;
    else if (table->n_philo == 1)
        return;

    // Crea i thread dei filosofi
    while (i < table->n_philo)
    {
        safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
        i++;
    }

    // Inizializza il tempo di inizio e indica che i filosofi possono iniziare
    safe_mutex(LOCK, &table->start_mutex);
    table->start_time = get_time();
    printf("Start time initialized to: %ld\n", table->start_time);
    table->all_threads_ready = true;  // Imposta `all_threads_ready` a true
    printf("All threads ready set to true\n");
    safe_mutex(UNLOCK, &table->start_mutex);

    // Attendi la fine di tutti i filosofi
    i = 0;
    while (i < table->n_philo)
    {
        safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
        i++;
    }
}



t_fork *get_first_fork(t_philo *philo) {
    if (philo->left_fork->fork_id < philo->right_fork->fork_id) {
        return philo->left_fork;
    }
    return philo->right_fork;
}

t_fork *get_second_fork(t_philo *philo) {
    if (philo->left_fork->fork_id > philo->right_fork->fork_id) {
        return philo->left_fork;
    }
    return philo->right_fork;
}

bool try_take_forks(t_philo *philo) {
    t_fork *first_fork = get_first_fork(philo);
    t_fork *second_fork = get_second_fork(philo);

    if (philo->table->end)
        return false;

    // Blocco il mutex delle forchette
    safe_mutex(LOCK, &first_fork->mutex);
    write_status(philo->table, philo->id, FORK);
    safe_mutex(LOCK, &second_fork->mutex);
    write_status(philo->table, philo->id, FORK);

    return true;
}

void eat(t_philo *philo)
{
    // Blocca il mutex della forchetta sinistra
    safe_mutex(LOCK, &philo->left_fork->mutex);
    write_status(FORK, philo);

    // Blocca il mutex della forchetta destra
    safe_mutex(LOCK, &philo->right_fork->mutex);
    write_status(FORK, philo);

    // Filosofo sta mangiando
    write_status(EATING, philo);
    set_long(&philo->mutex, &philo->last_meal, get_time());
    philo->eat_count++;
    precise_usleep(philo->table->time_to_eat, philo->table);

    // Se ha raggiunto il limite dei pasti
    if (philo->table->eat_limit > 0 && philo->eat_count >= philo->table->eat_limit)
        set_bool(&philo->mutex, &philo->is_full, true);

    // Rilascia il mutex delle forchette
    safe_mutex(UNLOCK, &philo->left_fork->mutex);
    safe_mutex(UNLOCK, &philo->right_fork->mutex);      
}


void eating_phase(t_philo *philo)
{
	size_t start_time;

	safe_mutex(LOCK, &philo->table->death);
	philo->last_meal = current_time_in_ms();
	philo->eat_count++;
	if (philo->table->eat_limit != -1 && philo->eat_count >= philo->table->eat_limit)
	{
		philo->is_full = true;
	}
	safe_mutex(UNLOCK, &philo->table->death);

	write_status(philo->table, philo->id, EATING);
	
	start_time = current_time_in_ms();
	while ((current_time_in_ms() - start_time) < (size_t)philo->table->time_to_eat)
		usleep(500);
} 


static void think(t_philo *philo)
{
	write_status(THINKING, philo);
}


void *philo_life(void *arg) {
    t_philo *philo = (t_philo *)arg;
    wait_all_threads(philo->table);

    while (!simulation_end(philo->table) && !philo->is_full) {
        if (!try_take_forks(philo)) {
            continue;
        }
		//eat
        eat(philo);
		//sleep
        write_status(SLEEPING, philo);
        precise_usleep(philo->table->time_to_sleep, philo->table);
		//think
        think(philo);
		//repeat tunz tunz letsowski
    }
    return NULL;
}

bool try_take_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	if (philo->table->end)
		return false;

	// Determina l'ordine delle forchette per evitare deadlock
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}

	safe_mutex(LOCK, &first_fork->mutex);
	write_status(philo->table, philo->id, FORK);
	safe_mutex(LOCK, &second_fork->mutex);
	write_status(philo->table, philo->id, FORK);

	return true;
}

void eating_phase(t_philo *philo)
{
	size_t start_time;

	safe_mutex(LOCK, &philo->table->death);
	philo->last_meal = current_time_in_ms();
	philo->eat_count++;
	if (philo->table->eat_limit != -1 && philo->eat_count >= philo->table->eat_limit)
	{
		philo->is_full = true;
	}
	safe_mutex(UNLOCK, &philo->table->death);

	write_status(philo->table, philo->id, EATING);
	
	start_time = current_time_in_ms();
	while ((current_time_in_ms() - start_time) < (size_t)philo->table->time_to_eat)
		usleep(500);
}


void *philo_life(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	// set last meal time
	while (!simulation_end(philo->table))
	{
		if (philo->is_full)
			break ;
		//eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		//think(philo);
		break ;
	}
	return (NULL);
} 


void start_simulation(t_table *table)
{
	pthread_t monitor;
	int i;

	table->start_time = current_time_in_ms();
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
		i++;
	}
	safe_thread(&monitor, monitor_philosophers, table, CREATE);
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
		i++;
	}
	safe_thread(&monitor, NULL, NULL, JOIN);
}

*/