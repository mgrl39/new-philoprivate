/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:59:57 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/06 14:05:57 by meghribe         ###   ########.fr       */
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
 * time_code -> SECONDS MSECS USECS
 *
 * Is gonna set the seconds and the microseconds
 * TODO: IF I USE time_code that is not there the compiler will complain
 */
long	gettime(t_time_code	time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed!");
	if (MSEC == time_code)
		return ((tv.tv_sec * 1e3) + tv.tv_usec / 1e3);
	else if (USEC == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (-1);
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
 * 2) REFINE LAST USECS WITH SPINLOCK
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

	start = gettime(USEC);
	if (start == -1)
		ft_alert(MSG_ERR_GET_TIME, ALERT_ERROR);
	// TODO CHECK IF GETTIME IS -1
	// TODO CHECK IF GETTIME IS -1
	while (gettime(USEC) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		// TODO CHECK IF GETTIME IS -1
		elapsed = gettime(USEC) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			// TODO CHECK IF GETTIME IS -1
			while (gettime(USEC) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(RED "%s\n" RESET, error);
	exit(EXIT_FAILURE);
}
