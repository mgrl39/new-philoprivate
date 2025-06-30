/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/29 11:41:02 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>

/**
 * Initializes the mutexes required for the simulation
 *
 * Allocates and initializes one mutex per fork, as well as separate mutexes for
 * writing output, meal tracking, and death detection.
 *
 * @param table Pointer to the shared table structure
 * @return 0 on succes, 1 on failure
 */
int	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (ft_error(MSG_MALLOC_ERR));
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (free(table->forks), ft_error(MSG_MALLOC_ERR));
		i++;
	}
	// TODO SI FALLAN DEBO HACER FREES ARRIBA...
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (ft_error(MSG_MALLOC_ERR));
	if (pthread_mutex_init(&table->meal_lock, NULL))
		return (ft_error(MSG_MALLOC_ERR));
	if (pthread_mutex_init(&table->death_lock, NULL))
		return (ft_error(MSG_MALLOC_ERR));
	return (SUCCESS);
}

/**
 * Initializes the philosohers structures
 *
 * Allocates memory for each philosopher and sets their IDs, 
 * pointer to the shared table
 * and assigns the correspondign left and right forks (mutex pointers).
 *
 * @param table Pointer to the shared table structure.
 * @return 0 on succes, 1 on failure
 */
// TODO: cambiar a una nueva funcion de clean 
// SI EL MALLOC DE table->philos = NULL; 
// falla, se generan leaks porque el de mutexes ya esta puesto
int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (free(table->forks), ft_error(MSG_MALLOC_ERR));
	i = 0;
	memset(table->philos, 0, sizeof(t_philo) * table->num_philos);
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].forks[LEFT] = &table->forks[i];
		table->philos[i].forks[RIGHT] = \
			&table->forks[(i + 1) % table->num_philos];
		if (table->num_philos == 1)
			table->philos[i].forks[RIGHT] = NULL;
		i++;
	}
	return (SUCCESS);
}
