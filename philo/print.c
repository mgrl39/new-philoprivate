/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:22:46 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/29 09:11:01 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

static void	print_colored_status(long new_time, t_philo *philo, char *msg)
{
	printf("%06ld %d ", new_time, philo->id);
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

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;
	long	adjusted_time;

	if (!philo || !msg || !philo->table)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	if (!check_death_flag(philo->table))
	{
		timestamp = get_time();
		if (timestamp != -1)
		{
			adjusted_time = timestamp - philo->table->start_time;
			print_colored_status(adjusted_time, philo, msg);
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
