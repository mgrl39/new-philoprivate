/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:24:08 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/21 01:50:57 by meghribe         ###   ########.fr       */
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

/* Error Messages */
# define MSG_USAGE "Usage: ./philo n_philos t_die t_eat t_sleep [n_meals]"
# define MSG_INVALID_ARGS "Error: Arguments must be positive integers"
# define MSG_MALLOC_ERR "Error: memory allocation failed"
# define MSG_THREAD_ERR "Error: Thread creation failed"
# define MSG_MUTEX_ERR "Error: Mutex initialization failed"

/* Status Messages */
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"

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

typedef struct s_philo	t_philo;

typedef enum e_fork_side
{
	LEFT = 0,
	RIGHT = 1
}	t_fork_side;

typedef struct s_data
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_meals;
	int		all_ate;
	int		someone_died;
	long		start_time;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
	t_data			*data;
}	t_philo;

#endif
