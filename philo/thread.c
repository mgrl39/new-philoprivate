/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 00:31:30 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/10 00:32:03 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philos(t_table *table, int count)
{
	int	i;
	int	ret;

	i = 0;
	while (i < count)
	{
		ret = pthread_join(table->philos[i++].thread_id, NULL);
		if (ret)
			ft_alert(F_JOIN_THREAD, A_WARN);
	}
}

int	create_philos(t_table *table, int *created)
{
	int		i;
	t_philo	*phil;

	*created = 0;
	phil = &table->philos[0];
	if (table->philo_nbr == 1)
	{
		if (pthread_create(&phil->thread_id, 0, single_philo, phil))
			return (ft_alert(F_CREAT_ONE_PHILO, A_ERROR));
		*created = 1;
		return (SUCCESS);
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		phil = &table->philos[i];
		if (pthread_create(&phil->thread_id, 0, dinner_simulation, phil))
		{
			*created = i;
			return (ft_alert(F_CREAT_PHILO_THR, A_ERROR));
		}
		i++;
	}
	*created = i;
	return (SUCCESS);
}
