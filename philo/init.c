/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:18:54 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/03 11:07:10 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Takes:
 * a pointer to philosopher.
 * A pointer to the actual forks
 * Relative position in the table.
 * EVEN odd fork assigment
 */

// We have our philos, we have this array of structs and mutexes.
// When it comes to fork assigmnet.
// philo_id != relative position in the array  (we start by 0 and the first philo is id 1)
// Right fork -> Position of the fork
// Left fork is more treaky:
// 	- We are going focus in philo number 5: LEFT FORK OF PhilO number 5 is 0
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
		philo->second_fork = &forks[(philo_position + 1 % philo_nbr)];
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
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

// We want to init this mutex
// super useful for debug
void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
