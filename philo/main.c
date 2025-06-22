/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/21 01:39:02 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg)
{
	return (!!printf("%s%s%s\n", RED, msg, RESET));
}

int	check_args(int argc, char *argv[])
{
	return ((void)argc, (void)argv, 1);
}

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_error(MSG_USAGE));
	if (!check_args(argc, argv))
		return (ft_error(MSG_INVALID_ARGS));
	return (0);
	(void)argv;
}
