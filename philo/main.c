/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:43:06 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/05 21:17:08 by meghribe         ###   ########.fr       */
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
static int	process_arguments(t_table *table, char *av[])
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
	if (init_table(&table))
		return (1);
	dinner_start(&table);
	clean_table(&table);
	return (0);
}
