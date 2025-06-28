/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:10:03 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 14:27:30 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * TODO: REMOVE IN THE FUTURE
 * @brief Prints debug messages if DEBUG is enabled.
 *
 * @param format Format string like printf
 * @param ... Varibale arguments
 */
void	dp(const char *format, ...)
{
	va_list	args;

	if (DEBUG)
	{
		va_start(args, format);
		printf(GOLD);
		printf("[DEBUG] ");
		printf(RESET);
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
}
