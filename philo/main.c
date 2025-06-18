#include "philo.h"

void	ft_error(void)
{
	write(1, "ERROR", 5);
}

int	main(int argc, char *argv[])
{
	(void)argv;
	if (argc < 5 || argc > 6)
		ft_error();
	return (0);
}
