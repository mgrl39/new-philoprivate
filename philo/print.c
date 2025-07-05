/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:39 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/05 23:54:42 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

static void	write_status_debug(t_philo_status status, t_philo *philo,
			long time)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET
			BLUE" %d has taken the 1 fork\t\t\tn [ %d ]\n"RESET,
			time, philo->id, philo->second_fork->fork_id);
	else if (TAKE_SECOND_FORK == status
		&& !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET RED
			" %d has taken the 2 fork\n\t\t\tn [ %d ]\n"RESET,
			time, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is eating\t\t\tn [ %ld ]\n"RESET,
			time, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is sleeping\n", time, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is thinking\n", time, philo->id);
	else if (DIED == status)
		printf(RED"\t\t %6ld %d died \n"RESET, time, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	time;

	time = gettime(MILLISECOND);
	time -= philo->table->start_simulation;
	if (get_int(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (DEBUG_MODE)
		write_status_debug(status, philo, time);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(GOLD BOLD"%-6ld"RESET GOLD MSG_FORK, time, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(BOLD GREEN "%-6ld"RESET GREEN MSG_EAT, time, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(BLUE BOLD"%-6ld"RESET BLUE MSG_SLEEP, time, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(PURPLE BOLD"%-6ld"RESET PURPLE MSG_THINK, time, philo->id);
		else if (DIED == status)
			printf(BOLD RED"%-6ld" MSG_DIED RESET, time, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	ft_putstr_fd(char *msg, int fd)
{
	char	*s;

	if (!msg)
		return ;
	s = msg;
	while (*s)
		write(fd, s++, 1);
}

int	ft_alert(char *msg, t_alert_type type)
{
	if (type == ALERT_ERROR)
		ft_putstr_fd(RED, 2);
	else
		ft_putstr_fd(GOLD, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
	return (type == ALERT_ERROR);
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
