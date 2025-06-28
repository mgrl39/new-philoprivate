/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 03:26:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 11:29:24 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_philo_atoi(const char *str, int *result)
{
	size_t			i;
	long long		num;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	if (str[i] != '\0' || num == 0)
		return (0);
	*result = (int)num;
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
