/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:26:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/01 20:34:53 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Module containing wrapper funtions
 * with embedded controls on return
 */

void	*safe_malloc(size_t	bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}
/*
 * Embed controls on return status
 * pthread_mutex_init pthread_mutex_unlock pthread_mutex_lock and pthread_mutex_init()
 * This functions returns 0 if successful, otherwise we will get an error value.
 * We will recreate the perror function
 */
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	else if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value  specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK  == status)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on muttex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enogh memory to create antoher mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

// ** MUTEX SAFE **
// init
// destroy
// lock
// unlock
//
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

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
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be fould corresponding to that \
			specified by the given thraed ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies \
			the calling thread.");

}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle");
}
