/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:47:01 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/06 14:00:04 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Module containning setters_getters
 * to avoid writing LOCK UNLOCK everywhere
 * These functions now return int for error handling
 * Return 0 for succes, FAILURE (1) for errors
 */
int	set_int(t_mtx *mutex, int *dest, int value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_alert(FAIL_LOCK_SET_INT, A_ERROR));
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_alert(FAIL_UNLOCK_SET_INT, A_ERROR));
	return (0);
}

// READING thread safe
int	get_int(t_mtx *mutex, int *value)
{
	int	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (ft_alert(FAIL_LOCK_GET_INT, A_ERROR));
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_alert(FAIL_UNLOCK_GET_INT, A_ERROR));
	return (ret);
}

// LONG
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		return (ft_alert(FAIL_LOCK_GET_LONG, A_ERROR));
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_alert(FAIL_UNLOCK_GET_LONG, A_ERROR));
	return (ret);
}

int	set_long(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_alert(FAIL_LOCK_SET_LONG, A_ERROR));
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_alert(FAIL_UNLOCK_SET_LONG, A_ERROR));
	return (0);
}

int	simulation_finished(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end_simulation));
}
