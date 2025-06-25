/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/25 16:38:42 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints an error message and returns 1.
 *
 * @param msg The error message to print.
 * @return Always returns 1 (as boolean).
 */
int	ft_error(char *msg)
{
	return (!!printf("%s%s%s\n", RED, msg, RESET));
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
	clean_data(&data);
	return (0);
}
