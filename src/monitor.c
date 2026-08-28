#include	"../library/codexion.h"

void *monitor_routine(void *args)
{
	int	i;
	t_sumilation *simu = (t_sumilation*)args;
	long	current_time;
	long	last_compile;

	i = 0;
	while (1)
	{
		while (i < simu->data->number_of_coders)
		{
			current_time = get_time_of_ms();
			if (simu->coder[i].is_finished)
				return (NULL);
			pthread_mutex_lock(&simu->state_lock);
			last_compile = simu->coder[i].last_time_compilation;
			pthread_mutex_unlock(&simu->state_lock);
			if (current_time + last_compile > simu->data->time_to_burnout)
			{
				printf("%ld %d burned out\n", current_time - simu->start_time, simu->coder[i].id);
				simu->is_simulation_over = 1;
			}
			i++;
	}
	usleep(500);
	// Burnout check

	}
	return (NULL);
}




void create_monitor(t_sumilation *simu)
{
	pthread_t	monitor;
	pthread_create(&monitor, NULL, monitor_routine, (void*)simu);
	
}

