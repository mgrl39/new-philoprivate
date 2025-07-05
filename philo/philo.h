/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:44:41 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/06 00:46:24 by meghribe         ###   ########.fr       */
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

# define MSG_FORK 	" %d has taken a fork\n"
# define MSG_EAT 	" %d is eating\n"
# define MSG_SLEEP 	" %d is sleeping\n"
# define MSG_THINK 	" %d is thinking\n"
# define MSG_DIED 	" %d died\n"

/* ************************************************************************** */
/* ERRORS */
# define ERR_NOT_DIGIT	-1
# define ERR_NEGATIVE	-2
# define ERR_OVERFLOW	-3
# define ERR_ZERO_VALUE	-4
# define ERR_TIMESTAMP	-5

# define MSG_ERR_NOT_DIGIT "Error '%s' contains non-numeric characters. \
Please use only digits."
# define MSG_ERR_NEGATIVE "Error: '%s' is a negativee number. Please use only \
positive values."
# define MSG_ERR_OVERFLOW "Error: '%s' is too large. Maximum allowed value \
is %d."
# define MSG_ERR_TIMESTAMP "Error: all timings must be at least 60ms"
# define MSG_ERR_MALLOC "Error: malloc"
# define MSG_ERR_MUTEX "Error: mutex"

# define MSG_ARG_PHILOS 	"number of philosophers"
# define MSG_ARG_DIE_TIME 	"time to die"
# define MSG_ARG_EAT_TIME 	"time to eat"
# define MSG_ARG_SLEEP_TIME "time to sleep"
# define MSG_ARG_MEALS		"number of meals"

# define MIN_TIMESTAMP	60e3

# define MSG_WARN_FAIL_DEST_FORK_MTX "Warning: Failed to destroy fork mutex\n"
# define MSG_WARN_FAIL_DEST_TABLE_MTX "Warning: Failed to destroy table mutex\n"
# define MSG_WARN_FAIL_DEST_WRITE_MTX "Warning: Failed to destroy write mutex\n"

# define MSG_ERR_GET_TIME "Error: gettimeofday function returned -1\n"

/* ************************************************************************** */
# define DEBUG_MODE 0

/* Philosopher states */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

/* Operation code for mutex or thread functions */
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_opcode;

/* Codes for time units used in gettime() */
typedef enum e_time_code
{
	MILLISECOND,
	MICROSECOND
}	t_time_code;

typedef enum e_alert_type
{
	ALERT_ERROR,
	ALERT_WARNING
}	t_alert_type;

/* Typedefs */
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

/*
 * Fork structure holds mute an ID useful for debugging
 */
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
 * philo_mutex -> useful for races with the monitor
 */
typedef struct s_philo
{
	int			id;
	int			full;
	long		meals_counter;
	long		last_meal_time;
	t_mtx		philo_mutex;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	pthread_t	thread_id;
}	t_philo;

/*
 * TABLE
 * ./philo 5 800 200 200 [5]
 */
// amount of philosophers of the first value (argv[1])
// which is the argv[2]
// argv[3]
// argv[4]
/**
 * nbr_limit_meals will be act like the number or like a flag.
 * If its -1 we do not have the input.
 */
/*
 * This is basically the time when the simulation is starting.
 * This is important because I need time stamps	from the start of simulation
 * For the philosophers will  have timestamps starting from this value.
 */
/*
 * int end_simulation is very important which is triggered when a philo dies
 * or all philos are full. So this flag is turned on in these two scenarios.
 */
// all_threads_ready to syncro philosophers
/*
 * Is going to be the actual monitor thread, searching for death.
 */
// avoid races while reading from table
// this is the array of all the forks. FORK FORK FORK FORK FORK
// the array of all the philos. PHILO PHILO PHILO PHILO PHILO
typedef struct s_table
{
	int			end_simulation;
	int			all_threads_ready;
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		threads_running_nbr;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

/* Prototypes */
void	safe_thread_handle(
			pthread_t *thread,
			void *(*foo)(void *),
			void *data,
			t_opcode opcode);
void	*monitor_dinner(void *data);
void	error_exit(const char *error);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	set_long(t_mtx *mutex, long *dest, long value);
void	set_int(t_mtx *mutex, int *dest, int value);
void	wait_all_threads(t_table	*table);
void	write_status(t_philo_status status, t_philo *philo);
void	increase_long(t_mtx *mutex, long *value);
void	clean_table(t_table *table);
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, int pre_simulation);
void	prevent_simultaneous_start(t_philo *philo);
void	precise_usleep(long usec, t_table *table);
void	ft_putstr_fd(char *msg, int fd);
void	print_argument_error(
			int error,
			const char *arg,
			const char *param_name);

long	gettime(t_time_code	time_code);
long	get_long(t_mtx *mutex, long *value);

int		init_table(t_table *table);
int		ft_alert(char *msg, t_alert_type type);
int		get_int(t_mtx *mutex, int *value);
int		simulation_finished(t_table *table);
int		all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
int		validate_and_convert_to_long(const char *str, long *result);
#endif
