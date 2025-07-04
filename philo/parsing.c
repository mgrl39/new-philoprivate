/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:49:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/04 18:28:15 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>

void	print_argument_error(int error, const char *arg, const char *param_name)
{
	if (error == ERR_NOT_DIGIT)
		printf(RED MSG_ERR_NOT_DIGIT RESET "\n", arg);
	else if (error == ERR_NEGATIVE)
		printf(RED MSG_ERR_NEGATIVE RESET "\n", arg);
	else if (error == ERR_OVERFLOW)
		printf(RED MSG_ERR_OVERFLOW RESET "\n", arg, INT_MAX);
	else if (error == ERR_ZERO_VALUE)
		printf(RED "Error: %s (%s) cannot be zero." RESET "\n", \
		param_name, arg);
}

static inline int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * An inline function is a function that is expanded at 
 * the point of the function call
 * rather than being executed as a seprarte functionc all.
 * this is done to reduce the function call overhead and improve performance.
 */
static inline int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_philo_atol(const char *str, long *result)
{
	int			sign;
	size_t		i;
	long long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (ERR_NOT_DIGIT);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (ERR_OVERFLOW);
		i++;
	}
	if (str[i] != '\0')
		return (ERR_NOT_DIGIT);
	if (sign == -1)
		return (ERR_NEGATIVE);
	if (num == 0)
		return (ERR_ZERO_VALUE);
	*result = (long)num;
	return (1);
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

//// TODO
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
	if (av[5] && 
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
	{
		printf(RED MSG_ERR_TIMESTAMP RESET "\n");
		return (1);
	}
	return (0);
}

// TODO: CAMBIAR A FT_PUTSTR_FD o A FT_ERROR O A OTRA COSA...
void	print_parsing_error(int error_code, const char *arg)
{
	if (error_code == ERR_NOT_DIGIT)
		printf(RED MSG_ERR_NOT_DIGIT RESET "\n", arg);
	else if (error_code == ERR_NEGATIVE)
		printf(RED MSG_ERR_NEGATIVE RESET "\n", arg);
	else if (error_code == ERR_OVERFLOW)
		printf(RED "Error: '%s' is too large. maximum \
			allowed value is %d." RESET "\n", arg, INT_MAX);
	else if (error_code == ERR_ZERO_VALUE)
		printf(RED "Error: '%s' cannot be zero." RESET "\n", arg);
	else if (error_code == ERR_TIMESTAMP)
		printf(RED MSG_ERR_TIMESTAMP RESET "\n");
}
