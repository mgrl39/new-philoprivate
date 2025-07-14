/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:33 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/12 18:19:57 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;
	long	now;

	if (get_int(&philo->philo_mtx, &philo->full))
		return (0);
	now = gettime(MSEC);
	elapsed = now - get_long(&philo->philo_mtx, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	return (elapsed > t_to_die);
}

static void	check_philo_status(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr && !simulation_finished(table))
	{
		if (philo_died(table->philos + i))
		{
			set_int(&table->table_mtx, &table->end_simulation, 1);
			write_status(DIED, table->philos + i);
		}
	}
}

/*
 * TODO: Change this comment
 * make sure all philos running
 * spinlock till all thread run
 * constantly check time to die
 */
void	*monitor_dinner(void *data)
{
	t_table	*table;
	long	check_interval;

	table = (t_table *)data;
	check_interval = table->time_to_die / 10;
	if (check_interval > 1000)
		check_interval = 1000;
	else if (check_interval < 100)
		check_interval = 100;
	while (!all_threads_running(&table->table_mtx,
			&table->threads_running_nbr,
			table->philo_nbr))
		usleep(check_interval);
	while (!simulation_finished(table))
	{
		check_philo_status(table);
		usleep(100);
	}
	return (NULL);
}
