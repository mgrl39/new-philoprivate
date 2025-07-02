/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:47:01 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/01 21:54:30 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 *
 * Module containning setters_getters
 * to avoid writing LOCK UNLOCK everywhere
 */

// BOOL
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	// READING thread safe
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

// LONG
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
 * REDUDANT? Nah..
 */

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
