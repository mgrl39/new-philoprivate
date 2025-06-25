/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/25 15:44:35 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg)
{
	return (!!printf("%s%s%s\n", RED, msg, RESET));
}

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

static int	init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	if (init_mutexes(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

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
