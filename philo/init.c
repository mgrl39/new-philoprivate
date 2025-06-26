/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/26 09:09:32 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initializes the mutexes required for the simulation
 *
 * Allocates and initializes one mutex per fork, as well as separate mutexes for
 * writing output, meal tracking, and death detection.
 *
 * @param data Pointer to the shared data structure
 * @return 0 on succes, 1 on failure
 */
int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (ft_error(MSG_MALLOC_ERR));
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error(MSG_MALLOC_ERR));
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) \
			|| pthread_mutex_init(&data->meal_lock, NULL) \
			|| pthread_mutex_init(&data->death_lock, NULL))
		return (ft_error(MSG_MALLOC_ERR));
	return (0);
}

/**
 * Initializes the philosoher structures/
 *
 * Allocates memory for each philosopher and sets their IDs, 
 * pointer to the shared data
 * and assigns the correspondign left and right forks (mutex pointers).
 *
 * @param data Pointer to the shared data structure.
 * @return 0 on succes, 1 on failure
 */
int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (ft_error(MSG_MALLOC_ERR));
	i = 0;
	memset(data->philos, 0, sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].forks[LEFT] = &data->forks[i];
		data->philos[i].forks[RIGHT] = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
