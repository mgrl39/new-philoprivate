/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:22:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 17:48:10 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

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
				printf(BLUE "%s" RESET "\n", msg);
			else if (ft_strcmp(msg, MSG_THINK) == 0)
				printf(PURPLE "%s" RESET "\n", msg);
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

void	print_usage(char *argv[])
{
	printf(BLUE "\n=== PHILOSOPHERS USAGE GUIDE ===\n" RESET);
	printf("\nSyntax: " GOLD
		"%s num_philos time_to_die time_to_eat time_to_sleep [num_meals]"
		RESET "\n\n", argv[0]);
	printf("Parameters:\n");
	printf(" " PURPLE "num_philos	" RESET
		": Number of philosophers at the table\n");
	printf(" " PURPLE "time_to_die	" RESET
		": Time in ms until a philosopher dies from Starvation\n");
	printf(" " PURPLE "time_to_eat	" RESET
		": Time in ms it takes for a philosopher to eat\n");
	printf(" " PURPLE "time_to_sleep 	" RESET
		": Time in ms it takes for a philosopher to sleep\n");
	printf(" " PURPLE "num_meals	" RESET
		": [Optional] Number of times each must eat \n\n");
}
