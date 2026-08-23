#include "../library/codexion.h"

long	get_time_of_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_sumilation *sim, long target)
{
	long	current_time;

	current_time = get_time_of_ms();
	while (get_time_of_ms() < current_time + target)
	{
		if (sim->is_simulation_over)
			break;
		usleep(500);
	}
}

