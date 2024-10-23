/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:52:48 by fabi              #+#    #+#             */
/*   Updated: 2024/10/23 20:44:21 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_sleep(t_philo *philo)
{
    if (get_simulation_state(philo->table) != RUNNING) return;

    write_status(SLEEPING, philo);
    precise_usleep(philo->table->time_to_sleep / 1000, philo->table);
}


void think(t_philo *philo)
{
    write_status(THINKING, philo);
}

bool try_take_forks(t_philo *philo)
{
    t_fork *first_fork;
    t_fork *second_fork;

    if (simulation_end(philo->table)) return false;

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
    if (get_simulation_state(philo->table) != RUNNING) {
        safe_mutex(UNLOCK, &first_fork->mutex);
        return false;
    }
    write_status(FORK, philo);

    safe_mutex(LOCK, &second_fork->mutex);
    if (get_simulation_state(philo->table) != RUNNING) {
        safe_mutex(UNLOCK, &first_fork->mutex);
        safe_mutex(UNLOCK, &second_fork->mutex);
        return false;
    }
    write_status(FORK, philo);

    return true;
}

    

void eat(t_philo *philo)
{
    // Controlla se la simulazione è ancora in corso
    if (get_simulation_state(philo->table) != RUNNING) return;

    // Aggiorna il timestamp dell'ultimo pasto
    safe_mutex(LOCK, &philo->mutex);
    philo->last_meal = get_time();
    philo->eat_count++;
    safe_mutex(UNLOCK, &philo->mutex);

    write_status(EATING, philo);

    // Usa precise_usleep invece di un ciclo while
    precise_usleep(philo->table->time_to_eat / 1000, philo->table);
}



void *philo_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    //printf("[DEBUG] Philosopher %d starting\n", philo->id);

    // Aspetta che tutti i thread siano pronti
    while (!get_bool(&philo->table->start_mutex, &philo->table->all_threads_ready)) {
        if (get_simulation_state(philo->table) == END) {
            //printf("[DEBUG] Philosopher %d ending (simulation ended before start)\n", philo->id);
            return NULL;
        }
        precise_usleep(100, philo->table);
    }

    // Aggiungi un delay iniziale per i filosofi pari
    if (philo->id % 2 == 0) {
        precise_usleep(1000, philo->table);
    }

    // Ciclo principale del filosofo
    while (get_simulation_state(philo->table) == RUNNING)
    {
        // Se il filosofo ha raggiunto il limite di pasti, termina
        if (philo->table->eat_limit > 0 && philo->eat_count >= philo->table->eat_limit) {
            break;
        }

        if (get_simulation_state(philo->table) != RUNNING) break;

        think(philo);

        if (get_simulation_state(philo->table) != RUNNING) break;

        // Prova a prendere le forchette
        if (try_take_forks(philo))
        {
            if (get_simulation_state(philo->table) != RUNNING) {
                // Sblocca le forchette prima di uscire
                safe_mutex(UNLOCK, &philo->left_fork->mutex);
                safe_mutex(UNLOCK, &philo->right_fork->mutex);
                break;
            }

            // Se riesce a prendere le forchette, mangia
            eat(philo);

            // Sblocca le forchette dopo aver mangiato
            safe_mutex(UNLOCK, &philo->left_fork->mutex);
            safe_mutex(UNLOCK, &philo->right_fork->mutex);

            if (get_simulation_state(philo->table) == RUNNING) {
                philo_sleep(philo);
            }
        }

        // Piccola pausa per evitare di sovraccaricare la CPU
        if (get_simulation_state(philo->table) != RUNNING) break;
        precise_usleep(100, philo->table);
    }

    //printf("[DEBUG] Philosopher %d ending\n", philo->id);
    return NULL;
}




void start_simulation(t_table *table)
{
    int i;
    if (!table || table->n_philo <= 0)
        return;

    // Inizializza lo stato della simulazione a RUNNING
    set_simulation_state(table, RUNNING);
    
    //printf("[DEBUG] Starting simulation with %ld philosophers\n", table->n_philo);

    // Imposta il tempo di inizio prima di creare i thread
    table->start_time = get_time();
    //printf("[DEBUG] Start time set to: %ld\n", table->start_time);

    // Crea il thread per il controllo della morte prima dei filosofi
    safe_thread(&table->death_checker, death_checker, table, CREATE);
    //printf("[DEBUG] Death checker thread created\n");

    // Crea tutti i thread dei filosofi
    i = 0;
    while (i < table->n_philo)
    {
        //printf("[DEBUG] Creating philosopher thread %d\n", i + 1);
        safe_thread(&table->philos[i].thread, philo_life, &table->philos[i], CREATE);
        i++;
    }

    // Segnala che tutti i thread sono pronti
    safe_mutex(LOCK, &table->start_mutex);
    table->all_threads_ready = true;
    //printf("[DEBUG] All threads ready signal sent\n");
    safe_mutex(UNLOCK, &table->start_mutex);

    // Attendi la fine di tutti i thread
    i = 0;
    while (i < table->n_philo)
    {
        safe_thread(&table->philos[i].thread, NULL, NULL, JOIN);
        //printf("[DEBUG] Philosopher thread %d joined\n", i + 1);
        i++;
    }

    // Attendi il thread del death checker
    safe_thread(&table->death_checker, NULL, NULL, JOIN);
}