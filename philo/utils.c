/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:59:57 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/12 17:56:42 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

/*
 * pthread_mutex_init pthread_mutex_unlock pthread_mutex_lock 
 * and pthread_mutex_init()
 * This functions returns 0 if successful, otherwise we will get an error value.
 * We will recreate the perror function
 */

/*
 * We are gonna exploit gettimeofday
 * time_code -> MSEC USEC
 * In a future version can we handle more the gettimeofday return
 */
long	gettime(t_time_code	time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
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
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(USEC);
	if (start == -1)
		ft_alert(ERR_TIME_FN, A_ERROR);
	while (1)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(USEC) - start;
		if (elapsed >= usec)
			break ;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else if (remaining > 100)
			usleep(100);
		else
			usleep(10);
	}
}
