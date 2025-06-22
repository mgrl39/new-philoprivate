/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/22 04:57:26 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg)
{
	return (!!printf("%s%s%s\n", RED, msg, RESET));
}

static	int	check_args(int argc, char *argv[], t_data *data)
{
	if (!ft_philo_atoi(argv[1], &data->num_philos)
			|| !ft_philo_atoi(argv[2], &data->times.to_die)
			|| !ft_philo_atoi(argv[3], &data->times.to_eat)
			|| !ft_philo_atoi(argv[4], &data->times.to_sleep)
			|| (argc == 6 && \
				!ft_philo_atoi(argv[5], &data->num_meals)))
		return (ft_error(MSG_INVALID_ARGS));
	if (argc == 5)
		data->num_meals = -1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(MSG_USAGE));
	if (check_args(argc, argv, &data))
		return (1);
	return (0);
}
