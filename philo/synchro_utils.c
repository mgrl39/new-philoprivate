/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:56:40 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/02 17:55:43 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * SPINLOCK to Sncronize philos start
 */
void	wait_all_threads(t_table	*table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

/**
 * Monitor busy waits until all theads are not running
 */ // all threads ARE RUNNING
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr) 
{
	bool	ret;

	ret = false;

	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
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
