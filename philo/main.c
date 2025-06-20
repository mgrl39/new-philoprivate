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

void	ft_error(char *msg)
{
	printf("%s\n", msg);
}


int	check_args(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (1);
}
int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_error(RED MSG_USAGE RESET), 1);
	if (!check_args(argc, argv))
		return (ft_error(RED MSG_INVALID_ARGS), 1);
	return (0);
	(void)argv;
}
