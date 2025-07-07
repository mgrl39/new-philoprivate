/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadsafe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:26:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/06 13:49:06 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
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
