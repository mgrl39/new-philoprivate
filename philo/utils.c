/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:59:57 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/08 17:10:02 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
 * Embed controls on return status
 * pthread_mutex_init pthread_mutex_unlock pthread_mutex_lock 
 * and pthread_mutex_init()
 * This functions returns 0 if successful, otherwise we will get an error value.
 * We will recreate the perror function
 */

/** THREADS **/
/*
 * Threads errors
 */
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropiate permission\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && JOIN == opcode)
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be fould corresponding to that \
			specified by the given thraed ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies \
			the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else
		error_exit("wrong opcode for thread_handle");
}

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
		ft_alert(ERR_TIME_FN, A_ERROR);
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
		else if (remaining > 100)
			usleep(100);
		else
			usleep(10);
	}
}

void	error_exit(const char *error)
{
	printf(RED "%s\n" RESET, error);
	exit(EXIT_FAILURE);
}
