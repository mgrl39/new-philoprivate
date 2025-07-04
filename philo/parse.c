/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:49:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/04 21:41:19 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
