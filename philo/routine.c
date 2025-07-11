/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:21:28 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/11 22:06:26 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// Fake to lock the fork and sleep until the monitor will bust it.
void	*single_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	wait_all_threads(table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MSEC));
	increase_long(&table->table_mtx, &table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(table))
		usleep(200);
	return (NULL);
}

/**
 * If the system is:
 * EVEN, system already fair.
 * ODD, not always fair.
 */
void	thinking(t_philo *philo, int pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINK, philo);
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
 * Grab the forks: here first and second fork is handy
 * 	i dont worry about left right 
 * Eat: write eat, update last meal, update meals counter.
 * 	eventyally int full
 * Release the forks
 * Set the last meal time:
 * Actual eating. is set the last meal time and we
 * are gonna do it immediately.
 * sleep the time requested.
 * if is true the philo is full
 * unlock
 */
static int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork))
		return (ft_alert(F_LOCK_1, A_ERROR));
	// safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	// safe_mutex_handle(&philo->second_fork->fork, LOCK);
	if (pthread_mutex_lock(&philo->second_fork->fork))
	{
		if (pthread_mutex_unlock(&philo->first_fork->fork))
			ft_alert(F_UN_LOCK_2, A_ERROR);
		return (ft_alert(F_LOCK_2, A_ERROR));
	}
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MSEC));
	philo->meals_counter++;
	write_status(EAT, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mtx, &philo->full, 1);
	if (pthread_mutex_unlock(&philo->first_fork->fork))
		return (ft_alert(F_UNLOCK_1, A_ERROR));
	// safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	// safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	if (pthread_mutex_unlock(&philo->second_fork->fork))
		return (ft_alert(F_UNLOCK_2, A_ERROR));
	return (0);
}

/*
 * 0) Wait all philos, synchro start
 * 1) endless loop philo
 * set time last meal
 * syncro with monitor
 * increase a table variable cunter, with al threads running
 * desynchronizing philos
 * until the dinner is not finished
 * 1) the philosopher has to check: I am full? 
 * in that case i exit.
 * 2) EAT
 * sleep(philo);
 * 3) SLEEP -> write the actual status (write_status) & precise usleep
 * 4) THINK
 */
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running_nbr);
	prevent_simultaneous_start(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_int(&philo->philo_mtx, &philo->full))
			break ;
		if (eat(philo) == FAILURE)
		{
			break ;
		}
		write_status(SLEEP, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}

/**
 * If no meals, return
 * If only one philo -> function for this situation
 * Create all threads (all philos)
 * Create a monitor thread -> that is searching for philos which are death.
 * Syncronize the beggining of the simulation -> everytime you call 
 * pthread_create the philosophers start to run.
 * 	I want every philo start simultaneously. 
 * 	We need synchronization 
 * 	thing to make all the philos start at the same time.
 * join (wait) everyone.
 */
int	dinner_start(t_table *table)
{
	int	created;

	if (0 == table->nbr_limit_meals)
		return (SUCCESS);
	if (create_philos(table, &created))
	{
		set_int(&table->table_mtx, &table->end_simulation, 1);
		set_int(&table->table_mtx, &table->all_threads_ready, 1);
		return (join_philos(table, created), FAILURE);
	}
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table))
	{
		ft_alert(F_CREAT_MONITOR_TH, A_ERROR);
		set_int(&table->table_mtx, &table->end_simulation, 1);
		set_int(&table->table_mtx, &table->all_threads_ready, 1);
		return (join_philos(table, created), FAILURE);
	}
	table->start_simulation = gettime(MSEC);
	set_int(&table->table_mtx, &table->all_threads_ready, 1);
	join_philos(table, table->philo_nbr);
	set_int(&table->table_mtx, &table->end_simulation, 1);
	if (pthread_join(table->monitor, NULL))
		ft_alert(F_JOIN_MONITOR_THR, A_WARN);
	return (SUCCESS);
}
