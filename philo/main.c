/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:43:06 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/30 21:16:17 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * The main is a TL;DR of the program
 * We are gonna check if the input given at the command line is correct
 * we are going to kick in the Machinery 
 * Otherwise we're going to prompt the user to please feed me with correct prompt.
 *
 * ./philo 5 800 200 200 [5]
 * ./philo philosophers time_to_die time_to_eat time_to_sleep potencially_number_or_meals
 */
int	main(int ac, char **av)
{
	t_table	table;
	if (5 == ac || 6 == ac)
	{
		parse_input(&table);
	}
	else
	{
		// The input is wrong
		error_exit("Wrong input:\n"
				BLUE"Correct is ./philo 5 800 200 200 [5]"RESET);
	}
}
