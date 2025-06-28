/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 17:47:42 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @return int 1 on success, 0 on failure
 */
static int	validate_arg(char *arg, int *value, char *param, int zero_allow)
{
	int	result;

	result = ft_philo_atoi(arg, value);
	if (result <= 0)
	{
		if (result == ERR_ZERO_VALUE && zero_allow)
			return (1);
		if (result == ERR_ZERO_VALUE && !zero_allow && \
				(!ft_strcmp(param, MSG_ARG_PHILOS)))
			ft_error(MSG_ERR_ZERO_PHILO);
		else
			print_argument_error(result, arg, param);
		return (0);
	}
	return (1);
}

/**
 * @return 1 on succes, 0 on failure
 */
static	int	check_args(int ac, char *av[], t_table *table)
{
	if (!validate_arg(av[1], &table->num_philos, MSG_ARG_PHILOS, 0))
		return (1);
	if (!validate_arg(av[2], &table->time_to_die, MSG_ARG_DIE_TIME, 0))
		return (1);
	if (!validate_arg(av[3], &table->time_to_eat, MSG_ARG_EAT_TIME, 0))
		return (1);
	if (!validate_arg(av[4], &table->time_to_sleep, MSG_ARG_SLEEP_TIME, 0))
		return (1);
	if (ac == 6 && !validate_arg(av[5], &table->num_meals, MSG_ARG_MEALS, 1))
		return (1);
	if ((ac == 6 && table->num_meals == 0) || (ac == 5))
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

int	start_simulation(t_table	*table)
{
	int	i;

	i = 0;
	dp("Iniciando start_simulation");
	table->start_time = get_time();
	while (i < table->num_philos)
		table->philos[i++].last_meal_time = table->start_time;
	i = 0;
	while (i < table->num_philos)
	{
		dp("creando hilo para filosofo %d", i + 1);
		if (pthread_create(&table->philos[i].thread, NULL, \
				philo_loop, &table->philos[i]))
		{
			dp("Error al crear hilo para filosofo %d", i + 1);
			return (ft_error(MSG_THREAD_ERR));
		}
		dp("hilo para filosofo %d creado con exito", i + 1);
		i++;
	}
	dp("Todos los hilos creados, iniciando monitoreo");
	monitor_simulation(table);
	dp("Monitoreo terminado, esperando a que terminen los hilos");
	i = 0;
	while (i < table->num_philos)
	{
		dp("Esperando a que termine el hilo del filosofo %d", i + 1);
		pthread_join(table->philos[i++].thread, NULL);
		dp("Hilo del filosofo %d terminado", i + 1);
	}
	dp("Todos los hilos terminados");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (print_usage(argv), 1);
	memset(&table, 0, sizeof(t_table));
	dp("Validando argumentos");
	if (check_args(argc, argv, &table))
		return (print_usage(argv), 1);
	dp("Inicializando datos");
	if (init_table(&table))
		return (1);
	dp("Inicializando simulacion");
	if (start_simulation(&table))
		return (clean_table(&table), 1);
	dp("Simulacion terminada");
	return (clean_table(&table), 0);
}
