/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 16:47:26 by meghribe         ###   ########.fr       */
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

	dp("Reservando memoria para tenedores");
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
	{
		dp("Error en malloc de tenedores");
		return (ft_error(MSG_MALLOC_ERR));
	}
	i = 0;
	while (i < table->num_philos)
	{
		dp("Inicializando mutex para tenedor %d", i);
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			dp("Error al inicializar mutex de tenedor %d", i);
			return (ft_error(MSG_MALLOC_ERR));
		}
		i++;
	}
	dp("inicializando mutex de escritura");
	if (pthread_mutex_init(&table->write_lock, NULL))
	{
		dp("Error al inicializar mutex de escritura");
		return (ft_error(MSG_MALLOC_ERR));
	}
	if (pthread_mutex_init(&table->meal_lock, NULL))
	{
		dp("Error al inciailziar mutex de comidas");
		return (ft_error(MSG_MALLOC_ERR));
	}
	if (pthread_mutex_init(&table->death_lock, NULL))
	{
		dp("Error al inicailizar mutex de muerte");
		return (ft_error(MSG_MALLOC_ERR));
	}
	dp("Todos los mutexes inicializados correctamente");
	return (0);
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
int	init_philos(t_table *table)
{
	int	i;

	dp("Reservado memoria para filosofos");
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
	{
		dp("Error en malloc de filosofos");
		return (ft_error(MSG_MALLOC_ERR));
	}
	i = 0;
	dp("Inicializando memoria de filsofs con ceros");
	memset(table->philos, 0, sizeof(t_philo) * table->num_philos);
	while (i < table->num_philos)
	{
		dp("Configurando filosofo %d", i + 1);
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].forks[LEFT] = &table->forks[i];
		table->philos[i].forks[RIGHT] = \
			&table->forks[(i + 1) % table->num_philos];
		if (table->num_philos == 1)
		{
			dp("Solo hay un filosofo, fijando tenedor derecho a NULL");
			table->philos[i].forks[RIGHT] = NULL;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Initializes the shared table structure and all related resources.
 *
 * Sets all memory to zero, then initializes mutexes and philosophers.
 *
 * @param table Pointer to the shared table structure
 * return 0 on succes, 1 on failure.
 */
int	init_table(t_table *table)
{
	dp("Iniciando init_table");
	dp("Tiempo de inicio: %ld", table->start_time);
	dp("Iniciando mutexes");
	if (init_mutexes(table))
		return (1);
	dp("Iniciando filosofos");
	if (init_philos(table))
		return (1);
	dp("Init_table() completado con exito");
	return (0);
}
