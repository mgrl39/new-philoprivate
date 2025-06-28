/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 08:21:29 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 12:12:01 by meghribe         ###   ########.fr       */
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
int	check_death_flag(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->death_lock);
	result = table->someone_died;
	pthread_mutex_unlock(&table->death_lock);
	return (result);
}

/**
 * Checks if a pilosopher has died of starvation
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
 */
int	check_all_ate(t_table *table)
{
	int	i;
	int	finished_eating;

	debug_print("En check_all_ate: num_meals=%d", table->num_meals);
	if (table->num_meals == -1)
	{
		debug_print("No hay limite de comidas, retornando 0");
		return (0);
	}
	finished_eating = 0;
	pthread_mutex_lock(&table->meal_lock);
	i = 0;
	while (i < table->num_philos)
	{
		debug_print("Filosofo %d ha comido %d veces (necesita %d)",
			i + 1, table->philos[i].meals_eaten, table->num_meals);
		if (table->philos[i].meals_eaten >= table->num_meals)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	debug_print("%d de %d filosofos han comido suficiente",
		finished_eating, table->num_philos);
	if (finished_eating == table->num_philos)
	{
		debug_print("Todos los filosofos han comido suficiente!");
		return (set_death_flag(table), 1);
	}
	debug_print("No todos los filosofso han comido suficiente");
	return (0);
}

void	monitor_simulation(t_table *table)
{
	int	i;

	debug_print("Monitor inicializado");
	usleep(5000);
	while (!check_death_flag(table))
	{
		i = 0;
		while (i < table->num_philos && !check_death_flag(table))
		{
			debug_print("Verificando si filosofo %d ha muerto", i + 1);
			if (check_philo_death(&table->philos[i]))
			{
				debug_print("Filosofo %d ha muerto!", i + 1);
				return ;
			}
			i++;
		}
		debug_print("Verificando si todos han comido suficiente");
		if (check_all_ate(table))
		{
			debug_print("Todos los filosofos han comido suficiente");
			return ;
		}
		usleep(1000);
	}
	debug_print("Monitor terminado");
}
