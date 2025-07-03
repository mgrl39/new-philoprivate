/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:49:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 15:09:30 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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

/**
 * 1) Check for negatives --> if is there negative numbers -> this does'nt make
 * 		any sense so the input is wrong.
 * 2) Check if the number is legit (i can have spaces, 
 * i can have a +, i can have numebers and later bullshit
 * o
 * 3) Check for INT_MAX --> I will check
 *	 for len first, 2147483647 if len > 10, sure > INT_MAX
 * 	still check the number...
 *
 * Why return ptr? The function is going to return the numberr in string
 * // len of str
   // 1) skip spaces.
 */
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Feed me only positive values u suck!");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big. INT_MAX is the limit");
	return (number);
}

// always initialize
// 12313aa --> 12313
/**
 * The big work has been done by valid_input.
 * This is correct because in valid_input we are checking the len
 */
static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}

/**
 * ./philo 5 800 200 200 [5]
 * 	  argv[1] argv[2] argv[3] argv[4] argv[5]
 * 	  We need to convert this strings in actual integers, values.
 * 	  Doing that, i want to control:
 * 	  	- If the strings are actual numbers.
 * 	  	- Not major than INT_MAX
 * 	  	- timestamps > 60ms
 */
// Now check the timestamp > 60ms
// Now we have to check argv[5]
// As a flag
void	process_arguments(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
