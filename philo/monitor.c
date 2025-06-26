/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 08:21:29 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/26 08:12:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death_flag(t_data *data)
{
	(void)data;
	pthread_mutex_lock(&data->death_lock);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_lock);
}
