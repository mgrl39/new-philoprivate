/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:14:10 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/08 19:20:29 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static inline int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static void	trim_start_and_sign(const char *str, size_t	*i, int	*sign)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
}

int	validate_and_convert_to_long(const char *str, long *result)
{
	int			sign;
	size_t		i;
	long long	num;

	i = 0;
	num = 0;
	sign = 1;
	trim_start_and_sign(str, &i, &sign);
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
