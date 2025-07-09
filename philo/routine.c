/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:21:28 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/09 23:38:07 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/**
 * 1) Fake to lock the fork.
 * 2) Sleep until the monitor will bust it.
 */
void	*single_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	wait_all_threads(table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&table->table_mutex, &table->threads_running_nbr);
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
static int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork))
		return (ft_alert("Failed to lock first fork", A_ERROR));
	// safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	// safe_mutex_handle(&philo->second_fork->fork, LOCK);
	if (pthread_mutex_lock(&philo->second_fork->fork))
	{
		if (pthread_mutex_unlock(&philo->first_fork->fork))
			ft_alert("Failed to unlock first fork after second fork lock failure", A_ERROR);
		return (ft_alert("Failed to lock second fork", A_ERROR));
	}
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	philo->meals_counter++;
	write_status(EAT, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	if (pthread_mutex_unlock(&philo->first_fork->fork))
		return (ft_alert("SOME ALERT", A_ERROR));
	// safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	// safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	if (pthread_mutex_unlock(&philo->second_fork->fork))
		return (ft_alert("SOME ALERT", A_ERROR));
	// if OK retunr 0
	return (0);
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
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	prevent_simultaneous_start(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_int(&philo->philo_mutex, &philo->full))
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
/*
int	dinner_start(t_table *table)
{
	int	i;
	int	j;

	if (0 == table->nbr_limit_meals)
		return (SUCCESS);
	if (1 == table->philo_nbr)
	{
		//safe_thread_handle(&table->philos[0].thread_id, single_philo, &table->philos[0], CREATE);
		if (pthread_create(&table->philos[0].thread_id, NULL, single_philo,&table->philos[0]))
			return (ft_alert("ERROR CREATE 1 PHILO", A_ERROR));
	}
	else
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
//			safe_thread_handle(&table->philos[i].thread_id,	dinner_simulation, &table->philos[i], CREATE);
			if (pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]))
			{
				j = 0;
				while (j < i)
					pthread_join(table->philos[j++].thread_id, NULL);
				return (ft_alert("ERROR CREATING PHILOS", A_ERROR));
			}
		}
	}
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table))
	{
		j = 0;
		while (j < table->philo_nbr)
			pthread_join(table->philos[j++].thread_id, NULL);
		return (ft_alert("ERROR CREATE MONITOR", A_ERROR));
	}
	//safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MSEC);
	set_int(&table->table_mutex, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		// TODO CLEAN QUE BRO XD
		// safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (ft_alert(ERR_JOIN, A_ERROR));
	set_int(&table->table_mutex, &table->end_simulation, 1);
	// safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	if (pthread_join(table->monitor, NULL))
		return (ft_alert("ERROR JOIN", A_ERROR));
	return (SUCCESS);
}*/

static void	join_philos(t_table *table, int count)
{
	int	i;
	int	ret;

	i = 0;
	while (i < count)
	{
		ret = pthread_join(table->philos[i++].thread_id, NULL);
		if (ret)
			ft_alert(F_JOIN_THREAD, A_WARNING);
	}
}

static int	create_philos(t_table *table, int *created)
{
	int	i;

	*created = 0;
	if (table->philo_nbr == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL, single_philo, &table->philos[0]))
			return (ft_alert(F_CREAT_ONE_PHILO, A_ERROR));
		*created = 1;
		return (SUCCESS);
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]))
		{
			*created = i;
			return (ft_alert(F_CREAT_PHILO_THR, A_ERROR));
		}
		i++;
	}
	*created = i;
	return (SUCCESS);
}

int	dinner_start(t_table *table)
{
	int	created;

	if (0 == table->nbr_limit_meals)
		return (SUCCESS);
	if (create_philos(table, &created))
	{
		set_int(&table->table_mutex, &table->end_simulation, 1);
		set_int(&table->table_mutex, &table->all_threads_ready, 1);
		return (join_philos(table, created), FAILURE);
	}
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table))
	{
		ft_alert(F_CREAT_MONITOR_TH, A_ERROR);
		set_int(&table->table_mutex, &table->end_simulation, 1);
		set_int(&table->table_mutex, &table->all_threads_ready, 1);
		return (join_philos(table, created), FAILURE);
	}
	table->start_simulation = gettime(MSEC);
	set_int(&table->table_mutex, &table->all_threads_ready, 1);
	join_philos(table, table->philo_nbr);
	set_int(&table->table_mutex, &table->end_simulation, 1);
	if (pthread_join(table->monitor, NULL))
		ft_alert(F_JOIN_MONITOR_THR, A_WARNING);
	return (SUCCESS);
}
