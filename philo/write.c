/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:54:00 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/01 23:23:47 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * The same as write, just with more info
 * helping when debuging
 */

// TODO: IS SHOWD AT 1:27:38
static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	//elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	(void)elapsed;
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf("%6ld %d has taken the 1 fork", elapsed, philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf("%6ld %d has taken the 2 fork", elapsed, philo->first_fork->fork_id);
}

/**
 * [time_ms] [philo_id] [action]
 *
 * Has to be thread safe (write_mutex)
 */

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed; // the actual time
	
	elapsed = gettime(MILLISECOND);

	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);

	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_FIRST_FORK == status)
				&& !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET" %d has taken a fork\n", elapsed - philo->table->start_simulation, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET" %d is eating\n", elapsed - philo->table->start_simulation, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET" %d is sleeping\n", elapsed - philo->table->start_simulation, philo->id);
		else if (DIED == status)
			printf(BOLD"%-6ld %d died\n"RESET, elapsed - philo->table->start_simulation, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
