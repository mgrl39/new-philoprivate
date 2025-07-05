/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:56:40 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/05 20:55:26 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// SPINLOCK to Sncronize philos start
void	wait_all_threads(t_table	*table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

/**
 * Monitor busy waits until all theads are not running
 * All threads are running
 */
int	all_threads_running(t_mtx *mtx, long *threads_count, long total_threads)
{
	int	all_running;

	if (!mtx || !threads_count)
		return (0);
	safe_mutex_handle(mtx, LOCK);
	all_running = (*threads_count == total_threads);
	safe_mutex_handle(mtx, UNLOCK);
	return (all_running);
}

/**
 * We are going to lock the table mutex
 * and a pointer to the actual value
 *
 * increase threads running to synchro
 * with the monitor.
 *
 * The monitor will use all_threads_running to
 * indeed fetch this value and make a comparison
 * if the nmber of threads running is equal to
 * the actual total number of threads.
 */
void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

/* This tries to make the system fair */
void	prevent_simultaneous_start(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, 1);
	}
}
