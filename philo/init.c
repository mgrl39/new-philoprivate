/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/22 07:37:19 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->locks.forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->locks.forks)
		return (ft_error(MSG_MALLOC_ERR));
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->locks.forks[i], NULL))
			return (ft_error(MSG_MALLOC_ERR));
		i++;
	}
	if (pthread_mutex_init(&data->locks.write_lock, NULL) \
			|| pthread_mutex_init(&data->locks.meal_lock, NULL) \
			|| pthread_mutex_init(&data->locks.death_lock, NULL))
		return (ft_error(MSG_MALLOC_ERR));
	return (0);
}

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
		data->philos[i].forks[LEFT] = &data->locks.forks[i];
		data->philos[i].forks[RIGHT] = &data->locks.forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
