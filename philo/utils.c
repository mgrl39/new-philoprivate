/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 03:26:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/29 10:17:21 by meghribe         ###   ########.fr       */
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
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
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
	*result = (int)num;
	return (1);
}

// TODO: CHECK WHAT WILL HAPPEN WITH THE -1
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	return (ft_putstr_fd("\n", 2), FAILURE);
}
