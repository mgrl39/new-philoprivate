/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:43:06 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 18:26:37 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

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
	process_arguments(&table, argv);
	data_init(&table);
	dinner_start(&table);
	clean_table(&table);
	return (0);
}
