/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 03:26:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 08:31:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "limits.h"

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

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!philo || !msg || !philo->data)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_death_flag(philo->data))
	{
		timestamp = get_time();
		if (timestamp != -1)
		{
			timestamp -= philo->data->start_time;
			printf("%6ld %d %s\n", timestamp, philo->id, msg);
		}
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

/**
 * @brief Prints an error message and returns 1.
 *
 * @param msg The error message to print.
 * @return Always returns 1 (as boolean).
 */
int	ft_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	return (ft_putstr_fd("\n", 2), 1);
}

