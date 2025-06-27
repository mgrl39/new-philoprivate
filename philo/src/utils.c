/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 03:26:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/27 12:32:59 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

/**
 * TEMPORAL THING
 * @brief Prints debug messages if DEBUG is enabled.
 *
 * @param format Format string like printf
 * @param ... Varibale arguments
 */
void	debug_print(const char *format, ...)
{
	va_list	args;

	if (DEBUG)
	{
		va_start(args, format);
		printf(GOLD);
		printf("[DEBUG] ");
		printf(RESET);
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
}

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!philo || !msg || !philo->table)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	if (!check_death_flag(philo->table))
	{
		timestamp = get_time();
		if (timestamp != -1)
		{
			timestamp -= philo->table->start_time;
			printf("%06ld %d ", timestamp, philo->id);
			if (ft_strcmp(msg, MSG_FORK) == 0)
				printf(GOLD "%s" RESET "\n", msg);
			else if (ft_strcmp(msg, MSG_EAT) == 0)
				printf(GREEN "%s" RESET "\n", msg);
			else if (ft_strcmp(msg, MSG_SLEEP) == 0)
				printf("\033[38;5;75m%s" RESET "\n", msg);
			else if (ft_strcmp(msg, MSG_THINK) == 0)
				printf("\033[38;5;147m%s" RESET "\n", msg);
			else if (ft_strcmp(msg, MSG_DIED) == 0)
				printf(RED "%s" RESET "\n", msg);
			else
				printf("%s\n", msg);
		}
	}
	pthread_mutex_unlock(&philo->table->write_lock);
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
