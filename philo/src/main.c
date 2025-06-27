/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 12:32:29 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Parses and validates command line arguments.
 *
 * Converts arguments to integers and checks validity. 
 * Sets default for num meals if not provided.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param table Pointer to the shared table structure
 * @return 0 on succes, 1 on failure
 */
static	int	check_args(int argc, char *argv[], t_table *table)
{
	if (!ft_philo_atoi(argv[1], &table->num_philos)
		|| !ft_philo_atoi(argv[2], &table->time_to_die)
		|| !ft_philo_atoi(argv[3], &table->time_to_eat)
		|| !ft_philo_atoi(argv[4], &table->time_to_sleep)
		|| (argc == 6 && !ft_philo_atoi(argv[5], &table->num_meals)))
		return (ft_error(MSG_INVALID_ARGS));
	if ((argc == 6 && table->num_meals == 0) || (argc == 5))
		table->num_meals = -1;
	return (0);
}

/**
 * @brief cleans up and frees all allocated resources.
 *
 * Destroys all mutexes and frees allocated memory for forks and philosophers.
 *
 * @param table Pointer to the shared table structure.
 */
void	clean_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->forks)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (pthread_mutex_destroy(&table->forks[i]) != 0)
				printf("%s" MSG_FORK_DESTROY_ERR "%s\n", RED, i, RESET);
			i++;
		}
		free(table->forks);
	}
	if (pthread_mutex_destroy(&table->write_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "write lock", RESET);
	if (pthread_mutex_destroy(&table->meal_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "meal lock", RESET);
	if (pthread_mutex_destroy(&table->death_lock) != 0)
		printf("%s" MSG_MUTEX_DESTROY_ERR "%s\n", RED, "death lock", RESET);
	if (table->philos)
		free(table->philos);
}

/**
 * Estaria bien meejorar la mierda esta de erro al crear hilo para filosofo.
 */
int	start_simulation(t_table	*table)
{
	int	i;

	i = 0;
	debug_print("Iniciando start_simulation");
	while (i < table->num_philos)
	{
		debug_print("creando hilo para filosofo %d", i + 1);
		if (pthread_create(&table->philos[i].thread, NULL, philo_loop, &table->philos[i]))
		{
			debug_print("Error al crear hilo para filosofo %d", i + 1);
			return (ft_error(MSG_THREAD_ERR));
		}
		debug_print("hilo para filosofo %d creado con exito", i + 1);
		i++;
	}
	debug_print("Todos los hilos creados, iniciando monitoreo");
	monitor_simulation(table);
	debug_print("Monitoreo terminado, esperando a que terminen los hilos");
	i = 0;
	while (i < table->num_philos)
	{
		debug_print("Esperando a que termine el hilo del filosofo %d", i + 1);
		pthread_join(table->philos[i++].thread, NULL);
		debug_print("Hilo del filosofo %d terminado", i + 1);
	}
	debug_print("Todos los hilos terminados");
	return (0);
}

/**
 * @brief Main entry point of the program.
 *
 * Parser arguments, initializes table, and performs cleanup.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on succes, 1 on failure.
 */
int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (ft_error(MSG_USAGE));
	memset(&table, 0, sizeof(t_table));
	debug_print("Validando argumentos");
	if (check_args(argc, argv, &table))
		return (1);
	debug_print("Inicializando datos");
	if (init_table(&table))
		return (1);
	debug_print("Inicializando simulacion");
	if (start_simulation(&table))
		return (clean_table(&table), 1);
	debug_print("Simulacion terminada");
	return (clean_table(&table), 0);
}
