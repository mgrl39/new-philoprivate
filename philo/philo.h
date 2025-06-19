/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:24:08 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/19 06:01:21 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*
 * memset, printf, malloc, free, write,
 * usleep, gettimeofday, pthread_create,
 * pthread_detach, pthread_join, pthread_mutex_init,
 * pthread_mutex_destroy, pthread_mutex_lock,
 * pthread_mutex_unlock
 */

# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"


/**
 * number_of_philosophers						-	
 * time_to_die									-
 * time_to_eat									-
 * time_to_sleep								-
 * number_of_times_each_philosopher_must_eat	-
 */

typedef enum e_fork_side
{
	LEFT = 0,
	RIGHT = 1
}	t_fork_side;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork[2];
}	t_philo;

# define MSG_VALID_ARGS "number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]"

#endif
