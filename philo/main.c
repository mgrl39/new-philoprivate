/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:43:06 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/05 20:39:12 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

// return 1 failure. Return 0 success
static int	parse_and_check(char *arg, long *value, char *param, int zeroable)
{
	int	result;

	result = ft_philo_atol(arg, value);
	if (result <= 0)
	{
		if (result == ERR_ZERO_VALUE && zeroable)
			return (0);
		else
			print_argument_error(result, arg, param);
		return (1);
	}
	return (0);
}

// return 1 failure. Return 0 success
int	process_arguments(t_table *table, char *av[])
{
	if (parse_and_check(av[1], &table->philo_nbr, MSG_ARG_PHILOS, 0))
		return (1);
	if (parse_and_check(av[2], &table->time_to_die, MSG_ARG_DIE_TIME, 0))
		return (1);
	if (parse_and_check(av[3], &table->time_to_eat, MSG_ARG_EAT_TIME, 0))
		return (1);
	if (parse_and_check(av[4], &table->time_to_sleep, MSG_ARG_SLEEP_TIME, 0))
		return (1);
	if (av[5] && \
		parse_and_check(av[5], &table->nbr_limit_meals, MSG_ARG_MEALS, 1))
		return (1);
	if (!av[5])
		table->nbr_limit_meals = -1;
	table->time_to_die *= 1e3;
	table->time_to_eat *= 1e3;
	table->time_to_sleep *= 1e3;
	if (table->time_to_die < MIN_TIMESTAMP
		|| table->time_to_eat < MIN_TIMESTAMP
		|| table->time_to_sleep < MIN_TIMESTAMP)
		return (ft_error(MSG_ERR_TIMESTAMP));
	return (0);
}
/*
 * The main is a TL;DR of the program
 * We are gonna check if the input given at the command line is correct
 * we are going to kick in the Machinery 
 * Otherwise we're going to prompt the user 
 * to please feed me with correct prompt.
 *
 * ./philo 5 800 200 200 [5]
 * ./philo philosophers time_to_die time_to_eat time_to_sleep 
 * potencially_number_or_meals
 */
int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (print_usage(*argv), 1);
	memset(&table, 0, sizeof(t_table));
	if (process_arguments(&table, argv))
		return (print_usage(*argv), 1);
	init_table(&table);
	dinner_start(&table);
	clean_table(&table);
	return (0);
}
