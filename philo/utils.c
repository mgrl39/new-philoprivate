#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	error_exit(const char *error)
{
	printf(RED "%s\n" RESET, error);
	exit(EXIT_FAILURE);
}
