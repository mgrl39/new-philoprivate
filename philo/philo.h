/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:24:08 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 12:10:39 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

/**
 * Numerro de filosofos
 * Tiempo amxximo sin comer (ms)
 * Tempo comiendo (ms)
 * Tiempo durmiendo (ms)
 * Comidas requeridas (-1 = infinito)
 * Bandera de muerte
 * Tiempo de inicio
 * Mutex para tenedores
 * Mutex para salida
 * Mutex para acceso a comidas
 * Mutex para acceso a muerte
 * Array de filosofos
 */
struct s_table
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
};

/**
 * ID del filosofo
 * Comidas consumidas
 * Ultimo timepo de comida
 * Tenedores [LEFT, RIGHT]
 * hilo del filosofo
 * Referencia a mesa compartida
 */
struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
	t_table			*table;
};

/* Function prototypes */
long	get_time(void);
void	print_status(t_philo *philo, char *msg);
void	*philo_loop(void *arg);
void	monitor_simulation(t_table *table);
int		check_death_flag(t_table *table);
int		init_table(t_table *table);
int		ft_error(char *msg);
int		ft_philo_atoi(const char *str, int *result);

/* Error Messages */
# define MSG_USAGE "Usage: ./philo n_philos t_die t_eat t_sleep [n_meals]"
# define MSG_INVALID_ARGS "Error: Invalid input. Use positive integers only."
# define MSG_THREAD_ERR "Error: Thread creation failed"
# define MSG_MALLOC_ERR "Error: Memory allocation failed"
# define MSG_MUTEX_ERR "Error: Mutex initialization failed"

/* Warning Messages */
# define MSG_MUTEX_DESTROY_ERR "Warning: Failed to destroy %s"
# define MSG_FORK_DESTROY_ERR "Warning: Failed to destroy fork mutex %d"

/* Status Messages */
# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"

/* Fork indices */
# define LEFT 0
# define RIGHT 1

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
# define BLUE	"\033[38;5;75m"
# define PURPLE	"\033[38;5;147m"

/**
 * ================================
 * DEBUG MODE DEBUG MODE DEBUG MODE 
 * ================================
 */
# define DEBUG 0

/* Debug function */
void	debug_print(const char *format, ...);

/**
 * ================================
 */
#endif
