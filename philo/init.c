/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:18:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/05 22:50:55 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/**
 * Takes:
 * a pointer to philosopher.
 * A pointer to the actual forks
 * Relative position in the table.
 * EVEN odd fork assigment
 */

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
static void	philo_init(t_table *table)
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
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

// Aux functin to clean mutexes
static void	cleanup_mutexes(t_table *table, int initialized_forks)
{
	int	i;
	int	status;

	i = -1;
	while (++i < initialized_forks)
	{
		status = pthread_mutex_destroy(&table->forks[i].fork);
		if (status != 0)
			ft_putstr_fd("Warning: Failed to destroy fork mutex\n", 2);
	}
	status = pthread_mutex_destroy(&table->table_mutex);
	if (status != 0)
		ft_putstr_fd("Warning: Failed to destroy table mutex\n", 2);
	status = pthread_mutex_destroy(&table->write_mutex);
	if (status != 0)
		ft_putstr_fd("Warning: Failed to destroy write mutex\n", 2);
}

// We want to init this mutex
// super useful for debug
// if bad return 1
//
int	init_table(t_table *table)
{
	int	i;
	int	destroy_status;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (ft_error(MSG_ERR_MALLOC));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (free(table->philos), ft_error(MSG_ERR_MUTEX));
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
	{
		destroy_status = pthread_mutex_destroy(&table->table_mutex);
		if (destroy_status != 0)
			ft_error("Warning: failed to destroy table mutex\n");
		return (free(table->philos), ft_error(MSG_ERR_MUTEX));
	}
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (cleanup_mutexes(table, 0), free(table->philos), ft_error(MSG_ERR_MALLOC));
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			cleanup_mutexes(table, i);
			free(table->philos);
			return (free(table->forks), ft_error(MSG_ERR_MUTEX));
		}
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (0);
}
