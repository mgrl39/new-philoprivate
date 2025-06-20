/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:23:51 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/21 00:55:15 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	printf("%s\n", msg);
}

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_error(RED MSG_USAGE RESET), 1);
	return (0);
	(void)argv;
}
