#include	"../library/codexion.h"

void *monitor_routine(void *args)
{
	int	i;
	t_sumilation *simu = (t_sumilation*)args;
	long	current_time;
	long	last_compile;

	while (1)
	{
		i = 0;
		while (i < simu->data->number_of_coders)
		{
			current_time = get_time_of_ms();
			if (simu->coder[i].is_finished)
				return (NULL);
			pthread_mutex_lock(&simu->state_lock);
			last_compile = simu->coder[i].last_time_compilation;
			pthread_mutex_unlock(&simu->state_lock);
			if (current_time - last_compile > simu->data->time_to_burnout)
			{
				pthread_mutex_lock(&simu->print_lock);
				printf("%ld %d burned out\n", current_time - simu->start_time, simu->coder[i].id);
				pthread_mutex_unlock(&simu->print_lock);
				simu->is_simulation_over = 1;
				return (NULL);
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

