/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:59:57 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 11:48:16 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * We are gonna exploit gettimeofday
 *
 * time_code -> SECONDS MILLISECONDS MICROSECONDS
 *
 * Is gonna set the seconds and the microseconds
 */
long	gettime(t_time_code	time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed!");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return (1337);
}

/**
 * precise usleep, the real one suck.
 * Indeed, the usleep is gonna give us at least the time we ask
 * but very often is going to give us more because opearting system lagging
 * things peculairrities.
 *
 * Every time we check if the simulation finished.
 *
 * 1) USLEEP THE MAJORITY OF TIME, NOT CPU INTENSIVE
 * 2) REFINE LAST MICROSECONDS WITH SPINLOCK
 *
 * This will give us more precise than the actual system function usleep
 * which is veey often not precise.
 */
// SPINLOCK
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(RED "%s\n" RESET, error);
	exit(EXIT_FAILURE);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
