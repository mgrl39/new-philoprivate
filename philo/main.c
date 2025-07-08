/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:43:06 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/08 21:12:09 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdio.h>

static void	print_usage(char *program_name)
{
	printf(BLUE"\n=== PHILOSOPHERS USAGE GUIDE ===\n" RESET);
	printf("\nSyntax: " GOLD
		"%s num_philos time_to_die time_to_eat time_to_sleep [num_meals]"
		RESET "\n\n", program_name);
	printf("Parameters:\n");
	printf(" " PURPLE "num_philos	" RESET
		": Number of philosophers at the table\n");
	printf(" " PURPLE "time_to_die	" RESET
		": Time in ms until a philosopher dies from Starvation\n");
	printf(" " PURPLE "time_to_eat	" RESET
		": Time in ms it takes for a philosopher to eat\n");
	printf(" " PURPLE "time_to_sleep 	" RESET
		": Time in ms it takes for a philosopher to sleep\n");
	printf(" " PURPLE "num_meals	" RESET
		": [Optional] Number of times each must eat \n\n");
}

// return 1 failure. Return 0 success
static int	parse_and_check(char *arg, long *value, int zeroable)
{
	int	parse_result;

	parse_result = validate_and_convert_to_long(arg, value);
	if (parse_result > 0)
		return (SUCCESS);
	if (parse_result == ERR_ZERO_VALUE && zeroable)
		return (SUCCESS);
	return (print_argument_error(parse_result), FAILURE);
}

// return 1 failure. Return 0 success
static int	process_arguments(t_table *table, char *av[])
{
	if (parse_and_check(av[1], &table->philo_nbr, 0))
		return (1);
	if (parse_and_check(av[2], &table->time_to_die, 0))
		return (1);
	if (parse_and_check(av[3], &table->time_to_eat, 0))
		return (1);
	if (parse_and_check(av[4], &table->time_to_sleep, 0))
		return (1);
	if (av[5] && \
		parse_and_check(av[5], &table->nbr_limit_meals, 1))
		return (1);
	if (!av[5])
		table->nbr_limit_meals = -1;
	table->time_to_die *= 1e3;
	table->time_to_eat *= 1e3;
	table->time_to_sleep *= 1e3;
	if (table->time_to_die < MIN_TIMESTAMP
		|| table->time_to_eat < MIN_TIMESTAMP
		|| table->time_to_sleep < MIN_TIMESTAMP)
		return (ft_alert(ERR_TIME, A_ERROR));
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
		return (print_usage(*argv), FAILURE);
	if (init_table(&table))
		return (FAILURE);
	if (dinner_start(&table) != SUCCESS)
		return (free_table(&table, table.philo_nbr), FAILURE);
	return (free_table(&table, table.philo_nbr), SUCCESS);
	// TODO clean philo mutexes
	//return (SUCCESS);
}
