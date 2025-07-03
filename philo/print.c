/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:39 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 14:07:09 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

/**
 * [time_ms] [philo_id] [action]
 *
 * thread safe
 * write_mutex
 */
static void	write_status_debug(t_philo_status status, t_philo *philo,
			long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET
			BLUE" %d has taken the 1 fork\t\t\tn [ %d ]\n"RESET,
			elapsed, philo->id, philo->second_fork->fork_id);
	else if (TAKE_SECOND_FORK == status
		&& !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET RED
			" %d has taken the 2 fork\n\t\t\tn [ %d ]\n"RESET,
			elapsed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is eating\t\t\tn [ %ld ]\n"RESET,
			elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t %6ld %d died \n"RESET, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND);
	elapsed -= philo->table->start_simulation;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET"%d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET"%d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET"%d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(BOLD"%-6ld"RESET"%d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(BOLD RED"%-6ld""%d died\n"RESET, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	print_usage(char *argv[])
{
	(void)argv;
}
