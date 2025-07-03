/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:39 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 18:12:28 by meghribe         ###   ########.fr       */
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
			long time)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET
			BLUE" %d has taken the 1 fork\t\t\tn [ %d ]\n"RESET,
			time, philo->id, philo->second_fork->fork_id);
	else if (TAKE_SECOND_FORK == status
		&& !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET RED
			" %d has taken the 2 fork\n\t\t\tn [ %d ]\n"RESET,
			time, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is eating\t\t\tn [ %ld ]\n"RESET,
			time, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is sleeping\n", time, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is thinking\n", time, philo->id);
	else if (DIED == status)
		printf(RED"\t\t %6ld %d died \n"RESET, time, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, int debug)
{
	long	time;

	time = gettime(MILLISECOND);
	time -= philo->table->start_simulation;
	if (get_int(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, time);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(GOLD BOLD"%-6ld"RESET GOLD MSG_FORK, time, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(BOLD GREEN "%-6ld"RESET GREEN MSG_EAT, time, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(BLUE BOLD"%-6ld"RESET BLUE MSG_SLEEP, time, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(PURPLE BOLD"%-6ld"RESET PURPLE MSG_THINK, time, philo->id);
		else if (DIED == status)
			printf(BOLD RED"%-6ld" MSG_DIED RESET, time, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	print_usage(char *program_name)
{
	printf(BLUE"\n=== PHILOSOPHERS USAGE GUIDE ===\n" RESET);
	printf("\nSyntax: " GOLD
		"%s num_philos time_to_die time_to_eat time_to_sleep [num_meals]"
		RESET "\n\n", program_name);
	printf("Parameters:\n");
	printf(" " PURPLE "num_philos	" RESET
		": Number of philosophers at the table\n");
	printf(" " PURPLE "time_to_die	" RESET
		": Time in ms until a philosopher dies from Starvation\n");
	printf(" " PURPLE "time_to_eat	" RESET
		": Time in ms it takes for a philosopher to eat\n");
	printf(" " PURPLE "time_to_sleep 	" RESET
		": Time in ms it takes for a philosopher to sleep\n");
	printf(" " PURPLE "num_meals	" RESET
		": [Optional] Number of times each must eat \n\n");
}
