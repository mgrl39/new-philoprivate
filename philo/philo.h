/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:44:41 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/02 18:42:43 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h> // printf
#include <stdlib.h> // malloc free
#include <unistd.h> // write, usleep (usleep is not so precise...)
#include <stdbool.h>
// contains all the functions
// all the functions containing mutexes and threads.
#include <pthread.h>  // mutex: init destroy lock unlock
		      // threads: create join detach
#include <sys/time.h> // gettimeofday (useful to get exactlly the time)
#include <limits.h> // INT_MAX
#include <errno.h>

/**
 * PHILO STATES
 */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

/*
 * Operation code fofr mutex or thread functions
 */
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;
//*** structures ***

/**
 * code more readable
 */
typedef pthread_mutex_t	t_mtx;

typedef	struct	s_table	t_table;
/*
 * FORK
 */
typedef struct	s_fork
{
	t_mtx	fork;
	int	fork_id; // This is very useful for debugging.Because i know exactly  which fork
			 // the philosopher is taking
			 //

}	t_fork;

/*
 * PHILO
 *
 *./philo 5 800 200 200 [5]
 */
typedef struct	s_philo
{
	int	id;
	long	meals_counter; // We will count the meals in this variable
	bool	full; // flag if the philosopher has eaten the maximum number of meals
	long	last_meal_time; // time passed from last meal. Is very important to check if the
				// philosopher has died. We will gonna have time to die
	t_fork	*first_fork;
	t_fork	*second_fork; // A pointer to the left fork and a pointer to the right fork
	pthread_t	thread_id; // A PHILO IS A THREAD. (this will be send to thread_create)
	t_mtx	philo_mutex; // useful for races with the monitor
	t_table	*table;
}	t_philo;

/*
 * TABLE
 * ./philo 5 800 200 200 [5]
 */
typedef	struct	s_table
{
	long	philo_nbr; // amount of philosophers of the first value (argv[1])
	long	time_to_die; // which is the argv[2]
	long	time_to_eat; // argv[3]
	long	time_to_sleep; // argv[4]
	long	nbr_limit_meals;
	/**
	 * nbr_limit_meals will be act like the number or like a flag.
	 * If its -1 we do not have the input.
	 */
	long	start_simulation; 
	/*
	 * This is basically the time when the simulation is starting.
	 * This is important because I need time stamps	from the start of simulation
	 * For the philosophers will  have timestamps starting from this value.
	 */
	bool	end_simulation;
	/*
	 * bool end_simulation is very important which is triggered when a philo dies
	 * or all philos are full. So this flag is turned on in these two scenarios.
	 */
	bool	all_threads_ready; // to syncro philosophers 
	/*
	 * Is going to be the actual monitor thread, searching for death.
	 */
	long	threads_running_nbr;
	pthread_t	monitor; 
	t_mtx	table_mutex; // avoid races while reading from table
	t_mtx	write_mutex;
	t_fork	*forks; // this is the array of all the forks. FORK FORK FORK FORK FORK
	t_philo *philos; // the array of all the philos. PHILO PHILO PHILO PHILO PHILO
}	t_table;

void	error_exit(const char *error);
void	parse_input(t_table *table, char **av);

# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"
# define BLUE	"\033[38;5;75m"
# define PURPLE	"\033[38;5;147m"
# define BOLD	"\033[1m"

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	data_init(t_table *table);


void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	simulation_finished(t_table *table);

void	wait_all_threads(t_table	*table);

/*
 * CODES for gettime
 */
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

long	gettime(t_time_code	time_code);
void	precise_usleep(long usec, t_table *table);

# define DEBUG_MODE 0
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	*safe_malloc(size_t	bytes);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	*monitor_dinner(void *data);
void	clean(t_table *table);
void	dinner_start(t_table *table);
#endif
