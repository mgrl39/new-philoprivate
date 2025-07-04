/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:48:19 by meghribe          #+#    #+#             */
/*   Updated: 2025/07/04 21:27:13 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>

// TODO: CAMBIAR A FT_PUTSTR_FD o A FT_ERROR O A OTRA COSA...
void	print_argument_error(int error, const char *arg, const char *param_name)
{
	if (error == ERR_NOT_DIGIT)
		printf(RED MSG_ERR_NOT_DIGIT RESET "\n", arg);
	else if (error == ERR_NEGATIVE)
		printf(RED MSG_ERR_NEGATIVE RESET "\n", arg);
	else if (error == ERR_OVERFLOW)
		printf(RED MSG_ERR_OVERFLOW RESET "\n", arg, INT_MAX);
	else if (error == ERR_ZERO_VALUE)
		printf(RED "Error: %s (%s) cannot be zero." RESET "\n", \
		param_name, arg);
}

// TODO: CAMBIAR A FT_PUTSTR_FD o A FT_ERROR O A OTRA COSA...
void	print_parsing_error(int error_code, const char *arg)
{
	if (error_code == ERR_NOT_DIGIT)
		printf(RED MSG_ERR_NOT_DIGIT RESET "\n", arg);
	else if (error_code == ERR_NEGATIVE)
		printf(RED MSG_ERR_NEGATIVE RESET "\n", arg);
	else if (error_code == ERR_OVERFLOW)
		printf(RED "Error: '%s' is too large. maximum \
			allowed value is %d." RESET "\n", arg, INT_MAX);
	else if (error_code == ERR_ZERO_VALUE)
		printf(RED "Error: '%s' cannot be zero." RESET "\n", arg);
	else if (error_code == ERR_TIMESTAMP)
		printf(RED MSG_ERR_TIMESTAMP RESET "\n");
}
