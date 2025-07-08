/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:50:39 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/08 20:32:36 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
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
	else if (EAT == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is eating\t\t\tn [ %ld ]\n"RESET,
			time, philo->id, philo->meals_counter);
	else if (SLEEP == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is sleeping\n", time, philo->id);
	else if (THINK == status && !simulation_finished(philo->table))
		printf(BOLD"%6ld"RESET" %d is thinking\n", time, philo->id);
	else if (DIED == status)
		printf(RED"\t\t %6ld %d died \n"RESET, time, philo->id);
}

int	write_status(t_philo_status status, t_philo *philo)
{
	long	time;

	time = gettime(MSEC);
	time -= philo->table->start_simulation;
	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	//safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (pthread_mutex_lock(&philo->table->write_mutex) != 0)
		return (ft_alert("ERROR UNLOCK MUTEX", A_ERROR));
	if (DEBUG_MODE)
		write_status_debug(status, philo, time);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(GOLD BOLD"%-6ld"RESET GOLD S_FORK, time, philo->id);
		else if (EAT == status && !simulation_finished(philo->table))
			printf(BOLD GREEN "%-6ld"RESET GREEN S_EAT, time, philo->id);
		else if (SLEEP == status && !simulation_finished(philo->table))
			printf(BLUE BOLD"%-6ld"RESET BLUE S_SLEEP, time, philo->id);
		else if (THINK == status && !simulation_finished(philo->table))
			printf(PURPLE BOLD"%-6ld"RESET PURPLE S_THINK, time, philo->id);
		else if (DIED == status)
			printf(BOLD RED"%-6ld" S_DIED RESET, time, philo->id);
	}
	// safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
	// TODO: check if this later...
	if (pthread_mutex_unlock(&philo->table->write_mutex) != 0)
		return (ft_alert("ERROR UNLOCK MUTEX", A_ERROR));
	return (0);
}

static void	ft_putstr_fd(char *msg, int fd)
{
	char	*s;

	if (!msg)
		return ;
	s = msg;
	while (*s)
		write(fd, s++, 1);
}

// TODO: MAYBE MUST LOCK THIS...
int	ft_alert(char *msg, t_alert_type type)
{
	if (type == A_ERROR)
		ft_putstr_fd(RED, 2);
	else
		ft_putstr_fd(GOLD, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\n", 2);
	return (type == A_ERROR);
}

// TODO: CHANGE IT TO FT_ALERT
void	print_argument_error(int error)
{
	if (error == ERR_NOT_DIGIT)
		ft_alert(ERR_DIT, A_ERROR);
	else if (error == ERR_NEGATIVE)
		ft_alert(ERR_NEG, A_ERROR);
	else if (error == ERR_OVERFLOW)
		ft_alert(ERR_LARGE, A_ERROR);
	else if (error == ERR_ZERO_VALUE)
		ft_alert(ERR_ZERO, A_ERROR);
}
