/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/26 08:46:00 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

/**
 * @brief Prints an error message and returns 1.
 *
 * @param msg The error message to print.
 * @return Always returns 1 (as boolean).
 */
int	ft_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	return (ft_putstr_fd("\n", 2), 1);
}

/**
 * @brief Parses and validates command line arguments.
 *
 * Converts arguments to integers and checks validity. 
 * Sets default for num meals if not provided.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param data Pointer to the shared data structure
 * @return 0 on succes, 1 on failure
 */
static	int	check_args(int argc, char *argv[], t_data *data)
{
	if (!ft_philo_atoi(argv[1], &data->num_philos)
		|| !ft_philo_atoi(argv[2], &data->time_to_die)
		|| !ft_philo_atoi(argv[3], &data->time_to_eat)
		|| !ft_philo_atoi(argv[4], &data->time_to_sleep)
		|| (argc == 6 && !ft_philo_atoi(argv[5], &data->num_meals)))
		return (ft_error(MSG_INVALID_ARGS));
	if (argc == 5)
		data->num_meals = -1;
	return (0);
}

/**
 * @brief Initializes the shared data structure and all related resources.
 *
 * Sets all memory to zero, then initializes mutexes and philosophers.
 *
 * @param data Pointer to the shared data structure
 * return 0 on succes, 1 on failure.
 */
static int	init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (init_mutexes(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

/**
 * @brief cleans up and frees all allocated resources.
 *
 * Destroys all mutexes and frees allocated memory for forks and philosophers.
 *
 * @param data Pointer to the shared data structure.
 */
void	clean_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (pthread_mutex_destroy(&data->forks[i]) != 0)
				printf("%s" MSG_FORK_DESTROY_ERR "%s\n", RED, i, RESET);
			i++;
		}
		free(data->forks);
	}
	if (pthread_mutex_destroy(&data->write_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "write lock", RESET);
	if (pthread_mutex_destroy(&data->meal_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "meal lock", RESET);
	if (pthread_mutex_destroy(&data->death_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "death lock", RESET);
	if (data->philos)
		free(data->philos);
}


int	start_simulation(t_data	*data)
{
	return ((void)data, 0);
}

/**
 * @brief Main entry point of the program.
 *
 * Parser arguments, initializes data, and performs cleanup.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on succes, 1 on failure.
 */
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(MSG_USAGE));
	if (check_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (start_simulation(&data))
		return (clean_data(&data), 1);
	return (clean_data(&data), 0);
}
