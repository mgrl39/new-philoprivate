/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:18:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/10 00:09:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	cleanup_philo_mtxes(t_table *table, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_destroy(&table->philos[i].philo_mtx))
			ft_alert(MSG_W_PHILO, A_WARNING);
	}
}

/**
 * Takes:
 * a pointer to philosopher.
 * A pointer to the actual forks
 * Relative position in the table.
 * EVEN odd fork assigment

// We have our philos, we have this array of structs and mutexes.
// When it comes to fork assigmnet.
// philo_id != relative position in the array 
// (we start by 0 and the first philo is id 1)
// Right fork -> Position of the fork
// Left fork is more treaky:
// 	- We are going focus in philo number 5: LEFT FORK OF 
// 	PhilO number 5 is 0
// 	- left_fork = (philo_pos + 1) % philo_nbr;
// 		(4 + 1) % 5 => 0 (left fork is 0)
//
// Indeed, every philo needs 2 forks to eat, that's what we need.
//
// == to position
// to prevent deadlock if its even its one way its is odd is another way
//
// Deadhlock happends when we have multiple threads to be stuck.
// We have a thread waiting.
// if you are the odd philosopher first you will ttake the left
// if you take the even takes the right
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

/**
 * We need to  initialize all the data of philo
 */
// super important function assign_forks
// "i" es basically the position in the table
static int	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->philo_mtx, NULL))
		{
			cleanup_philo_mtxes(table, i);
			return (ft_alert(ERR_MUTEX, A_ERROR));
		}
		assign_forks(philo, table->forks, i);
	}
	return (SUCCESS);
}

// Aux functin to clean mutexes
void	free_table(t_table *table, int initialized_forks)
{
	int	i;

	i = -1;
	while (++i < initialized_forks)
	{
		if (pthread_mutex_destroy(&table->forks[i].fork))
			ft_alert(MSG_W_FORK, A_WARNING);
	}
	if (pthread_mutex_destroy(&table->table_mtx))
		ft_alert(MSG_W_TABLE, A_WARNING);
	if (pthread_mutex_destroy(&table->write_mtx))
		ft_alert(MSG_W_WRITE, A_WARNING);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
}

/* 
 * We want to init this mutex
 * super useful for debug
 * if bad return 1
 */
int	init_table(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (ft_alert(ERR_MALLOC, A_ERROR));
	if (pthread_mutex_init(&table->table_mtx, NULL))
		return (free_table(table, 0), ft_alert(ERR_MUTEX, A_ERROR));
	if (pthread_mutex_init(&table->write_mtx, NULL))
		return (free_table(table, 0), ft_alert(ERR_MUTEX, A_ERROR));
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (free_table(table, 0), ft_alert(ERR_MALLOC, A_ERROR));
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL))
			return (free_table(table, i), ft_alert(ERR_MUTEX, A_ERROR));
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) == FAILURE)
		return (free_table(table, table->philo_nbr), FAILURE);
	return (SUCCESS);
}
