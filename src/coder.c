#include "../library/codexion.h"
#include <pthread.h>

long	get_time_of_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(t_sumilation *sim, long target)
{
	long	current_time;

	current_time = get_time_of_ms();
	while (get_time_of_ms() < current_time + target)
	{
		pthread_mutex_lock(&sim->state_lock);
		if (sim->is_simulation_over)
		{
			pthread_mutex_unlock(&sim->state_lock);
			return (0);
		}
		pthread_mutex_unlock(&sim->state_lock);
		usleep(500);
	}
	return (1);
}

