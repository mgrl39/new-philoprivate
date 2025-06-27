/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 07:01:23 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 08:57:28 by meghribe         ###   ########.fr       */
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

	debug_print("Reservando memoria para tenedores");
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		debug_print("Error en malloc de tenedores");
		return (ft_error(MSG_MALLOC_ERR));
	}
	i = 0;
	while (i < data->num_philos)
	{
		debug_print("Inicializando mutex para tenedor %d", i);
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			debug_print("Error al inicializar mutex de tenedor %d", i);
			return (ft_error(MSG_MALLOC_ERR));
		}
		i++;
	}
	debug_print("inicializando mutex de escritura");
	if (pthread_mutex_init(&data->write_lock, NULL))
	{
		debug_print("Error al inicializar mutex de escritura");
		return (ft_error(MSG_MALLOC_ERR));
	}
	if (pthread_mutex_init(&data->meal_lock, NULL))
	{
		debug_print("Error al inciailziar mutex de comidas");
		return (ft_error(MSG_MALLOC_ERR));
	}
	if (pthread_mutex_init(&data->death_lock, NULL))
	{
		debug_print("Error al inicailizar mutex de muerte");
		return (ft_error(MSG_MALLOC_ERR));
	}
	debug_print("Todos los mutexes inicializados correctamente");
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

	debug_print("Reservado memoria para filosofos");
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		debug_print("Error en malloc de filosofos");
		return (ft_error(MSG_MALLOC_ERR));
	}
	i = 0;
	debug_print("Inicializando memoria de filsofs con ceros");
	memset(data->philos, 0, sizeof(t_philo) * data->num_philos);
	while (i < data->num_philos)
	{
		debug_print("Configurando filosofo %d", i + 1);
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].forks[LEFT] = &data->forks[i];
		data->philos[i].forks[RIGHT] = &data->forks[(i + 1) % data->num_philos];
		if (data->num_philos == 1)
		{
			debug_print("Solo hay un filosofo, fijando tenedor derecho a NULL");
			data->philos[i].forks[RIGHT] = NULL;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Initializes the shared data structure and all related resources.
 *
 * Sets all memory to zero, then initializes mutexes and philosophers.
 *
 * @param data Pointer to the shared data structure
 * return 0 on succes, 1 on failure.
 */
int	init_data(t_data *data)
{
	debug_print("Iniciando init_data");
	memset(data, 0, sizeof(t_data));
	data->start_time = get_time();
	debug_print("Tiempo de inicio: %ld", data->start_time);
	debug_print("Iniciando mutexes");
	if (init_mutexes(data))
		return (1);
	debug_print("Iniciando filosofos");
	if (init_philos(data))
		return (1);
	debug_print("Init_data() completado con exito");
	return (0);
}
