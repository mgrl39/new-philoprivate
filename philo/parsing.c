/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:49:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/30 20:07:58 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 1) Check for negatives --> if is there negative numbers -> this does'nt make
 * 		any sense so the input is wrong.
 * 2) Check if the number is legit (i can have spaces, i can have a +, i can have numebers and later bullshit
 * o
 * 3) Check for INT_MAX --> I will check for len first, 2147483647 if len > 10, sure > INT_MAX
 * 	still check the number...
 *
 * Why reeturn ptr? The function is going to return the numberr in string
 */
static const char	*valid_input(const char *str)
{
	int	len; // len of str
	const char	*number;

	len = 0;
	// 1) skip spaces.
	while (
}

static long	ft_atol(const char *str)
{
	long	num;
}

/**
 * ./philo 5 800 200 200 [5]
 * 	  av[1] av[2] av[3] av[4] av[5]
 * 	  We need to convert this strings in actual integers, values.
 * 	  Doing that, i want to control:
 * 	  	- If the strings are actual numbers.
 * 	  	- Not major than INT_MAX
 * 	  	- timestamps > 60ms
 */
void	parse_input(t_table *table, char **av)
{
}
