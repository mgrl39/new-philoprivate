/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:33 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/08 20:33:56 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = gettime(MSEC);
	elapsed -= get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	return (elapsed > t_to_die);
}

/*
 * make sure all philos running
 * spinlock till all thread run
 * constantly check time to die
 */
void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;
	long	check_interval;

	table = (t_table *)data;
	check_interval = table->time_to_die / 10;
	if (check_interval > 1000)
		check_interval = 1000;
	else if (check_interval < 100)
		check_interval = 100;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr,
			table->philo_nbr))
		usleep(check_interval);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i);
				// TODO: AQUI VA UN break ; o no??
			}
		}
		usleep(100);
	}
	return (NULL);
}
