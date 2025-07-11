/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:47:01 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/11 22:08:49 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Module containing functions to avoid writing LOCK UNLOCK everywhere
 * These functions now return int for error handling
 * Return SUCCESS (0), FAILURE (1) for errors.
 */
int	set_int(t_mtx *mutex, int *dest, int value)
{
	if (pthread_mutex_lock(mutex))
		return (ft_alert(FAIL_LOCK_SET_INT, A_ERROR));
	*dest = value;
	if (pthread_mutex_unlock(mutex))
		return (ft_alert(FAIL_UNLOCK_SET_INT, A_ERROR));
	return (SUCCESS);
}

int	set_long(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex))
		return (ft_alert(FAIL_LOCK_SET_LONG, A_ERROR));
	*dest = value;
	if (pthread_mutex_unlock(mutex))
		return (ft_alert(FAIL_UNLOCK_SET_LONG, A_ERROR));
	return (SUCCESS);
}

// reading thread safe
int	get_int(t_mtx *mutex, int *value)
{
	int	ret;

	if (pthread_mutex_lock(mutex))
		return (-ft_alert(FAIL_LOCK_GET_INT, A_ERROR));
	ret = *value;
	if (pthread_mutex_unlock(mutex))
		return (-ft_alert(FAIL_UNLOCK_GET_INT, A_ERROR));
	return (ret);
}

// long 
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex))
		return (-ft_alert(FAIL_LOCK_GET_LONG, A_ERROR));
	ret = *value;
	if (pthread_mutex_unlock(mutex))
		return (-ft_alert(FAIL_UNLOCK_GET_LONG, A_ERROR));
	return (ret);
}

int	simulation_finished(t_table *table)
{
	return (get_int(&table->table_mtx, &table->end_simulation));
}
