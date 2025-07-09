/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:56:40 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/09 21:22:00 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// To sincronize philos start (now is not spinlock :D )
void	wait_all_threads(t_table	*table)
{
	while (!get_int(&table->table_mtx, &table->all_threads_ready))
		usleep(100);
}

/**
 * Monitor busy waits until all theads are not running
 * All threads are running
 * TODO: CHECK IF I AM RETURNING -1 RETURN -1 IF ERROR WITH MUTEX
 */
int	all_threads_running(t_mtx *mtx, long *threads_count, long total_threads)
{
	int	all_running;

	if (!mtx || !threads_count)
		return (0);
	if (pthread_mutex_lock(mtx))
		return (-ft_alert(FAIL_LOCK_THREAD_RUN, A_ERROR));
	//safe_mutex_handle(mtx, LOCK);
	all_running = (*threads_count == total_threads);
	if (pthread_mutex_unlock(mtx))
		return (-ft_alert(FAIL_UNLOCK_THREAD_RUN, A_ERROR));
	//safe_mutex_handle(mtx, UNLOCK);
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
int	increase_long(t_mtx *mutex, long *value)
{
	if (pthread_mutex_lock(mutex))
		return (ft_alert(FAIL_LOCK_INC_LONG, A_ERROR));
	(*value)++;
	if (pthread_mutex_unlock(mutex))
		return (ft_alert(FAIL_UNLOCK_INC_LONG, A_ERROR));
	return (SUCCESS);
}

/* 
 * Prevent all philos from starting at the same time,
 * to avoid simultaneous fork contention at the beggining.
 */
void	prevent_simultaneous_start(t_philo *philo)
{
	int	id;
	int	n;

	id = philo->id;
	n = philo->table->philo_nbr;
	if (n % 2 == 0 && id % 2 == 0)
		precise_usleep(3e4, philo->table);
	else if (n % 2 != 0 && id % 2 != 0)
		thinking(philo, 1);
}
