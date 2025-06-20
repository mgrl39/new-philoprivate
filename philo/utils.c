/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 03:26:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/21 00:45:53 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		mult;

	i = 0;
	res = 0;
	mult = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			mult = -1;
	while (nptr[i] >= 48 && nptr[i] <= 57)
		res = res * 10 + (nptr[i++] - 48);
	return (res * mult);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	get_time(void)
{
	struct timeval	tv;

	// TODO: return 0 for success, or -1 for failure.
	gettimeofday(&tv, NULL);
}
