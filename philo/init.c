/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/22 07:01:41 by meghribe         ###   ########.fr       */
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
