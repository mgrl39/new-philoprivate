/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:21:28 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/01 22:26:44 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// here is goonna be the actual simulation of the dinner
/*
 * 0) Wait all philos, synchro start
 * 1) endless loop philo
 */

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	/*
	 * until the dinner is not finished
	 */
	while (!simulation_finished(philo->table))
	{
		// 1) the philosopher has to check: I am full?
		// in that case i exit.
		if (philo->full) // TODO: THREAD SAFE
			break ;
		// 2) EAT
		eat(philo);
		// 3) SLEEP -> write the actual status (write_status) & precise usleep
		sleep(philo);
		// 4) THINK
		thinking(philo);

	}
	return (NULL);
}
/**
 * ./philo 5 800 200 200 [5]
 *
 * 0) If no meals, return -> [0]
 * 0.1) If only one philo -> we do an function for this situation.
 * 1) Create all threads, all philos
 * 2) Create a monitor thread -> thread that is searching for philsopher which are death.
 * 3) Syncronize the beggining of the simulation -> everytime you call pthread_create
 * 	the philosophers start to run.
 * 	I want every philo start simultaneously. We need synchronization thing to make
 * 	all the philos start at the same time.
 * 4) JOIN everyone
 */
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ; // back to main, clean
	else if (1 == table->philo_nbr)
		; // todo
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}

		// This is a while loop that is gonna be create all the threads, all the philosophers.
		// Every time this funciton is called immediately the thread starts running this dinner simulation function that we still have to do. 
		// So we need a synhronization thing to make all the philosophers start at the same time.
	
	// start of simulation
	table->start_simulation = gettime(MILLISECOND);
	/*
	 * we need a chronometer, we need a function that is able to give us back the 
	 * actual time. 
	 */
	// now all threads are ready!
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	// we are going to join (wait for everyone)
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	// If we manage to reach this line all philos are FULL.
}
