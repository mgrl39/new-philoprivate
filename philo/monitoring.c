/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:39:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/02 18:26:10 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 *
 * We have to check if the time from last_meal_time to last_meal is more than
 * time_to_die we set the value to true.
 *
 * maybe philo is full
 */
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;

	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int	i;
	t_table	*table;

	table = (t_table *)data;
	/**
	 * Here i'm going to need anohter syncrhonization thing which is that
	 * have to be absolutely sure that all the philosophers are running
	 * before starting their contols so i'm going to make sure all philos
	 * running
	 */
	// Monitor waits until all the threads are running. Spinlock till allt threads run
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table ->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
