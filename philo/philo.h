/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:44:41 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/11 21:24:44 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define RESET		"\033[0m"
# define RED		"\033[38;5;203m"
# define GOLD		"\033[38;5;220m"
# define GREEN		"\033[38;5;120m"
# define BLUE		"\033[38;5;75m"
# define PURPLE		"\033[38;5;147m"
# define BOLD		"\033[1m"

# define S_FORK 	" %d has taken a fork\n"
# define S_EAT		" %d is eating\n"
# define S_SLEEP 	" %d is sleeping\n"
# define S_THINK 	" %d is thinking\n"
# define S_DIED 	" %d died\n"

# define FAILURE 	1
# define SUCCESS 	0

/* ************************************************************************** */
# define ERR_NOT_DIGIT	-1
# define ERR_NEGATIVE	-2
# define ERR_OVERFLOW	-3
# define ERR_ZERO_VALUE	-4
# define ERR_TIMESTAMP	-5

# define ERR_DIT	"Error: Input contains non-numeric characters.\n"
# define ERR_NEG	"Error: Negative numbers are not allowed.\n"
# define ERR_LARGE	"Error: Number is too large.\n"
# define ERR_ZERO	"Error: Value cannot be zero.\n"
# define ERR_TIME	"Error: All timings must be at least 60ms.\n"
# define ERR_MALLOC	"Error: malloc.\n"
# define ERR_MUTEX	"Error: mutex.\n"
# define ERR_JOIN	"Error: Failed to join thread.\n"

# define MIN_TIMESTAMP	60e3

# define MSG_W_FORK		"Warning: Failed to destroy fork mutex\n"
# define MSG_W_TABLE	"Warning: Failed to destroy table mutex\n"
# define MSG_W_WRITE	"Warning: Failed to destroy write mutex\n"
# define MSG_W_PHILO	"Warning: Failed to destroy philo mutex\n"
# define ERR_TIME_FN	"Error: gettimeofday function returned -1\n"

/* ************************************************************************** */
# define DEBUG_MODE 0

/* Philosopher states */
typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

/* Codes for time units used in gettime() */
typedef enum e_time_code
{
	MSEC, // MILLISECOND
	USEC, // MICROSECOND
}	t_time_code;

typedef enum e_alert_type
{
	A_ERROR,
	A_WARN
}	t_alert_type;

/* Typedefs */
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

// Fork structure holds mutex an ID useful for debugging
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/*
 * PHILO
 *./philo 5 800 200 200 [5]
 * meals_counter -> We will count the meals in this variable
 * full -> flag if the philosopher has eaten the maximum number of meals
 * last_meal_time -> time passed from last meal. Is very important to check if
 * 			philosopher has died. We will gonna have time to die
 * thread_id -> a philo is a thread (this will be send to thread_create)
 * philo_mtx -> useful for races with the monitor
 */
typedef struct s_philo
{
	int			id;
	int			full;
	long		meals_counter;
	long		last_meal_time;
	t_mtx		philo_mtx;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	pthread_t	thread_id;
}	t_philo;

/*
 * nbr_limit_meals act like the number or like a flag.
 * philos have timestamps starting from start_simulation
 * all_threads_ready to syncro philosophers.
 * end_simulation is triggered when a philo dies or all philos are full.
 * monitor is ian actual monitor thread, searching for death.
 */
typedef struct s_table
{
	int			all_threads_ready;
	int			end_simulation;
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		threads_running_nbr;
	t_mtx		table_mtx;
	t_mtx		write_mtx;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

/* Prototypes */
void	free_table(t_table *table, int initialized_forks);
void	thinking(t_philo *philo, int pre_simulation);
void	prevent_simultaneous_start(t_philo *philo);
void	precise_usleep(long usec, t_table *table);
void	wait_all_threads(t_table	*table);
void	join_philos(t_table *table, int count);
void	*dinner_simulation(void *data);
void	*monitor_dinner(void *data);
void	*single_philo(void *arg);

long	gettime(t_time_code	time_code);
long	get_long(t_mtx *mutex, long *value);

int		all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
int		init_table(t_table *table);
int		ft_alert(char *msg, t_alert_type type);
int		get_int(t_mtx *mutex, int *value);
int		simulation_finished(t_table *table);
int		validate_and_convert_to_long(const char *str, long *result);
int		set_long(t_mtx *mutex, long *dest, long value);
int		set_int(t_mtx *mutex, int *dest, int value);
int		increase_long(t_mtx *mutex, long *value);
int		write_status(t_philo_status status, t_philo *philo);
int		dinner_start(t_table *table);
int		create_philos(t_table *table, int *created);

# define FAIL_LOCK_SET_INT		"Mutex lock failed in set_int"
# define FAIL_UNLOCK_SET_INT	"Mutex unlock failed in set_int"
# define FAIL_LOCK_GET_INT		"Mutex lock failed in get_int"
# define FAIL_UNLOCK_GET_INT	"Mutex unlock failed in get_int"
# define FAIL_LOCK_GET_LONG		"Mutex lock failed in get_long"
# define FAIL_UNLOCK_GET_LONG	"Mutex unlock failed in get_long"
# define FAIL_LOCK_SET_LONG		"Mutex lock failed in set_long"
# define FAIL_UNLOCK_SET_LONG	"Mutex unlock failed in set_long"
# define FAIL_LOCK_INC_LONG		"Mutex lock failed in increase_long"
# define FAIL_UNLOCK_INC_LONG	"Mutex unlock failed in increase_long"
# define FAIL_LOCK_THREAD_RUN	"Mutex lock failed in all_threads_running"
# define FAIL_UNLOCK_THREAD_RUN	"Mutex unlock failed in all_threads_running"

# define F_JOIN_THREAD			"Failed to join philosopher thread"
# define F_CREAT_ONE_PHILO		"Failed to create single philo thread"
# define F_CREAT_PHILO_THR		"Failed to create philosopher thread"
# define F_CREAT_MONITOR_TH		"Failed to create monitor thread"
# define F_JOIN_MONITOR_THR		"Failed to join monitor thread"

# define F_LOCK_1			"Failed to lock 1st fork"
# define F_LOCK_2			"Failed to lock 2nd fork"
# define F_UNLOCK_1			"Failed to unlock 1st fork"
# define F_UNLOCK_2			"Failed to unlock 2nd fork"
# define F_UN_LOCK_2		"Failed unlock 1st fork after 2nd fork lock failure"
#endif
