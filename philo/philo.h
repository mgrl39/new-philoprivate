/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:24:08 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/26 08:29:13 by meghribe         ###   ########.fr       */
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
# define MSG_INVALID_ARGS "Error: Invalid input. Use positive integers only."
# define MSG_THREAD_ERR "Error: Thread creation failed"
# define MSG_MALLOC_ERR "Error: Memory allocation failed"
# define MSG_MUTEX_ERR "Error: Mutex initialization failed"

/* Status Messages */
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"

/* Warning Messages */
# define MSG_MUTEX_DESTROY_ERR "Warning: Failed to destroy %s"
# define MSG_FORK_DESTROY_ERR "Warning: Failed to destroy fork mutex %d"

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

/* Fork indices */
# define LEFT 0
# define RIGHT 1

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				all_ate;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
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

/* Function prototypes */
int		ft_philo_atoi(const char *str, int *result);
void	print_status(t_philo *philo, char *msg);
long	get_time(void);
int		ft_error(char *msg);
int		init_philos(t_data *data);
int		init_mutexes(t_data *data);
void	*philosopher_routine(void *arg);

#endif
