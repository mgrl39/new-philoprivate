/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 06:53:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/26 07:34:57 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (!philo)
		return ;
	pthread_mutex_lock(philo->forks[LEFT]);
	print_status(philo, MSG_FORK);
	pthread_mutex_lock(philo->forks[RIGHT]);
	print_status(philo, MSG_FORK);
}

static void	eat(t_philo *philo)
{
	if (!philo)
		return ;
	print_status(philo, MSG_EAT);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->forks[RIGHT]);
	pthread_mutex_unlock(philo->forks[LEFT]);
}

static void	sleep_and_think(t_philo *philo)
{
	if (!philo)
		return ;
	print_status(philo, MSG_SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	print_status(philo, MSG_THINK);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died && (philo->data->num_meals == -1 \
	|| philo->meals_eaten < philo->data->num_meals))
	{
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
