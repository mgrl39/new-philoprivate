/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 06:53:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 09:41:32 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (!philo)
	{
		debug_print("Error: philo es NULL en take_forks");
		return ;
	}
	debug_print("Filosofo %d tomando tenedor izquierdo", philo->id);
	pthread_mutex_lock(philo->forks[LEFT]);
	print_status(philo, MSG_FORK);
	if (philo->forks[RIGHT])
	{
		debug_print("Filosofo %d tomando tenedor derecho", philo->id);
		pthread_mutex_lock(philo->forks[RIGHT]);
		print_status(philo, MSG_FORK);
	}
	else
		debug_print("Filosofo %d no tiene tenedor derecho", philo->id);
}

static void	eat(t_philo *philo)
{
	if (!philo)
	{
		debug_print("Error: philo es NULL en eat");
		return ;
	}
	if (!philo->forks[RIGHT])
	{
		debug_print("Filosofo %d no uede comer (solo tiene un tenedor)", philo->id);
		pthread_mutex_unlock(philo->forks[LEFT]);
		return ;
	}
	debug_print("Filosofo %d comienodo", philo->id);
	print_status(philo, MSG_EAT);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	debug_print("Filosofo %d actualizado: comidas=%d, ultimo tiempo=%ld",
			philo->id, philo->meals_eaten, philo->last_meal_time);
	pthread_mutex_unlock(&philo->table->meal_lock);
	usleep(philo->table->time_to_eat * 1000);
	debug_print("Filosofo %d soltando tenedores", philo->id);
	pthread_mutex_unlock(philo->forks[RIGHT]);
	pthread_mutex_unlock(philo->forks[LEFT]);
}

static void	sleep_and_think(t_philo *philo)
{
	if (!philo)
		return ;
	print_status(philo, MSG_SLEEP);
	usleep(philo->table->time_to_sleep * 1000);
	print_status(philo, MSG_THINK);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	debug_print("Filosofo %d iniciado", philo->id);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death_flag(philo->table) && (philo->table->num_meals == -1 \
	|| philo->meals_eaten < philo->table->num_meals))
	{
		debug_print("Filosofo %d intentando comer tenedores", philo->id);
		take_forks(philo);
		debug_print("Filosofo %d intentando comer", philo->id);
		eat(philo);
		if (philo->forks[RIGHT])
		{
			debug_print("filosofo %d intentando dormir y pensar", philo->id);
			sleep_and_think(philo);
		}
		else
		{
			debug_print("Filosofo %d esperando morir (sin tenedor derecho)", philo->id);
			usleep(1000);
		}
	}
	return (NULL);
}
