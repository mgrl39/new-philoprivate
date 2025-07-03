/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:44:41 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 15:15:23 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

# define RESET		"\033[0m"
# define RED		"\033[38;5;203m"
# define GOLD		"\033[38;5;220m"
# define GREEN		"\033[38;5;120m"
# define BLUE		"\033[38;5;75m"
# define PURPLE		"\033[38;5;147m"
# define BOLD		"\033[1m"

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
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

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
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
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
 * bool end_simulation is very important which is triggered when a philo dies
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
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

/* Prototypes */
void	safe_thread_handle(
			pthread_t *thread,
			void *(*foo)(void *),
			void *data,
			t_opcode opcode);
void	*safe_malloc(size_t	bytes);
void	*monitor_dinner(void *data);
void	error_exit(const char *error);
void	process_arguments(t_table *table, char *argv[]);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	data_init(t_table *table);
void	set_long(t_mtx *mutex, long *dest, long value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	wait_all_threads(t_table	*table);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	increase_long(t_mtx *mutex, long *value);
void	clean(t_table *table);
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);
void	print_usage(char *program_name);
void	precise_usleep(long usec, t_table *table);

long	gettime(t_time_code	time_code);
long	get_long(t_mtx *mutex, long *value);

bool	get_bool(t_mtx *mutex, bool *value);
bool	simulation_finished(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);

#endif
