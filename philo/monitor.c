/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 08:21:29 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 09:23:22 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Sets the death flag in a thread-safe manner
 */
void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}

/*
 * Checks if someone has died (thread-safe)
 */
int	check_death_flag(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

/**
 * Checks if a pilosopher has died of starvation
 */
int	check_philo_death(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (time_since_meal >= philo->data->time_to_die)
	{
		print_status(philo, MSG_DIED);
		set_death_flag(philo->data);
		return (1);
	}
	return (0);
}

/**
 * Checks if all philosophers have aeten enough meals
 */
int	check_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->num_meals == -1)
		return (0);
	finished_eating = 0;
	pthread_mutex_lock(&data->meal_lock);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten >= data->num_meals)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	if (finished_eating == data->num_philos)
		return (set_death_flag(data), 1);
	return (0);
}

void	monitor_simulation(t_data *data)
{
	int	i;

	debug_print("Monitor inicializado");
	usleep(5000);
	while (!check_death_flag(data))
	{
		i = 0;
		while (i < data->num_philos && !check_death_flag(data))
		{
			debug_print("Verificando si filosofo %d ha muerto", i + 1);
			if (check_philo_death(&data->philos[i]))
			{
				debug_print("Filosofo %d ha muerto!", i + 1);
				return ;
			}
			i++;
		}
		debug_print("Verificando si todos han comido suficiente");
		if (check_all_ate(data))
		{
			debug_print("Todos los filosofos han comido suficiente");
			return ;
		}
		usleep(1000);
	}
	debug_print("Monitor terminado");
}
