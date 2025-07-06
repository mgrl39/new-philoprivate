/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:21:28 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/06 13:06:57 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/**
 * 1) fake to lock the fork
 * 2) sleep until the monitor will bust it
 */
static void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

/**
 * if the system is even we dont care, system already fair.
 * ODD, not always fair.
 */
void	thinking(t_philo *philo, int pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

/**
 * MOST IMPORTANT THING FOR A PHILOSOPHER
 * eat routine
 * 1) grab the forks: here first and second fork is handy
 * 	i dont worry aboutt left irght
 * 2) eat: write eat, update last meal, update meals counter.
 * 	eventyally int full
 * 3) release the forks
 */
// 2) Set the last meal time:
// Actual eating. Now we have to set the last meal time and we
// are gonna do it immediately.
// sleep the time requested.
// if is true the philo is full
// 3) UNLOCK
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

// here is goonna be the actual simulation of the dinner
/*
 * 0) Wait all philos, synchro start
 * 1) endless loop philo
 */
// set time last meal
/**
 * syncro with monitor
 * increase a table variable cunter, with al threads running
 */
// desynchronizing philos
/*
 * until the dinner is not finished
 */
// 1) the philosopher has to check: I am full?
// in that case i exit.
//
// 2) EAT
// sleep(philo);
// 3) SLEEP -> write the actual status (write_status) & precise usleep
// 4) THINK
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	prevent_simultaneous_start(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_int(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}
/**
 * ./philo 5 800 200 200 [5]
 *
 * 0) If no meals, return -> [0]
 * 0.1) If only one philo -> we do an function for this situation.
 * 1) Create all threads, all philos
 * 2) Create a monitor thread -> thread that is searching for philsopher
 *	 which are death.
 * 3) Syncronize the beggining of the simulation -> everytime you call 
 * pthread_create the philosophers start to run.
 * 	I want every philo start simultaneously. We need synchronization 
 * 	thing to make all the philos start at the same time.
 * 4) JOIN everyone
 * back to main, clean
 * This is a while loop that is gonna be create all 
 * the threads, all the philosophers.
 * Every time this funciton is called immediately 
 * the thread starts running this dinner simulation function 
 * that we still have to do. 
 * So we need a synhronization thing to make 
 * all the philosophers start at the same time monitor
 * start of simulation
 * we need a chronometer, we need a function 
 * that is able to give us back the 
 * actual time. 
 */
// now all threads are ready!
// we are going to join (wait for everyone)
// If we manage to reach this line all philos are FULL.

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		safe_thread_handle(&table->philos[0].thread_id,
			single_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_int(&table->table_mutex, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_int(&table->table_mutex, &table->end_simulation, 1);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
