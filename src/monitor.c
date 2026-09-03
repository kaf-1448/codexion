#include	"../library/codexion.h"

static void	*monitor_routine(void *args)
{
	int	i;
	int	count;
	t_sumilation	*simu;
	long	current_time;
	long	last_compile;
	
	simu = (t_sumilation*)args;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < simu->data->number_of_coders)
		{

			if (simu->coder[i].is_finished == 1)
				count++;

			if (count == simu->data->number_of_coders)
				return (NULL);

			current_time = get_time_of_ms();
			pthread_mutex_lock(&simu->coder[i].coder_lock);
			last_compile = simu->coder[i].last_time_compilation;
			pthread_mutex_unlock(&simu->coder[i].coder_lock);


			if (current_time - last_compile > simu->data->time_to_burnout)
			{
				if (simu->coder[i].is_finished == 1)
				{
					i++;
					continue;
				}
				pthread_mutex_lock(&simu->state_lock);
				pthread_mutex_lock(&simu->print_lock);
				printf("%ld %d burned out\n", current_time - simu->start_time, simu->coder[i].id);
				simu->is_simulation_over = 1;
				pthread_mutex_unlock(&simu->print_lock);
				pthread_mutex_unlock(&simu->state_lock);
				return (NULL);
			}
			
			i++;
		}
		usleep(500);
	}
	
	return (NULL);
}

void	create_monitor(t_sumilation *simu)
{
	pthread_create(&simu->monitor_id, NULL, monitor_routine, (void*)simu);
}

