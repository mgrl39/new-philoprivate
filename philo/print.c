/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:22:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 11:30:05 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_strcmp(char *s1, char *s2)
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

/**
 * @brief Prints a message in the fd
 *
 * @param s The message
 * @param fd The file descriptor
 */
static void	ft_putstr_fd(char *s, int fd)
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
