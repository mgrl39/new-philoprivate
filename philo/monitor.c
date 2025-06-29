/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 08:21:29 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/29 10:54:58 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/**
 * Sets the death flag in a thread-safe manner
 */
void	set_death_flag(t_table *table)
{
	pthread_mutex_lock(&table->death_lock);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_lock);
}

/*
 * Checks if someone has died (thread-safe)
 */
int	is_simulation_terminated(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->death_lock);
	result = table->someone_died;
	pthread_mutex_unlock(&table->death_lock);
	return (result);
}

/**
 * Checks if a pilosopher has starved to death.
 *
 * Calculates the time elapsed since the philosopher's last meal. If this
 * time exceeds the `time_to_die` threshold, the philosopher is masked as dead,
 * and the simulation is terminated.
 *
 * @param philo Pointer to the Philosopher sstructure
 * @return 1 iif the philosopherr has died of starvation, 0 otherwise.
 */
int	check_philo_death(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&philo->table->meal_lock);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (time_since_meal >= philo->table->time_to_die)
	{
		print_status(philo, MSG_DIED);
		set_death_flag(philo->table);
		return (1);
	}
	return (0);
}

/**
 * Checks if all philosophers have aeten enough meals
 * Si no hay limite de comidas, devuelve 0
 */
int	check_all_ate(t_table *table)
{
	int	i;
	int	finished_eating;

	if (table->num_meals == -1)
		return (0);
	finished_eating = 0;
	pthread_mutex_lock(&table->meal_lock);
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philos[i].meals_eaten >= table->num_meals)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	if (finished_eating == table->num_philos)
		return (set_death_flag(table), 1);
	return (0);
}

void	monitor_simulation(t_table *table)
{
	int	i;

	usleep(500);
	while (!is_simulation_terminated(table))
	{
		i = 0;
		while (i < table->num_philos && !is_simulation_terminated(table))
		{
			if (check_philo_death(&table->philos[i]))
				return ;
			i++;
		}
		if (check_all_ate(table))
			return ;
		usleep(1000);
	}
}
