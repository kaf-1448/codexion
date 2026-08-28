#include	"../library/codexion.h"

void *monitor_routine(void *args)
{
	int	i;
	t_sumilation *simu = (t_sumilation*)args;

	i = 0;
	while (1)
	{
		while (i < simu->data->number_of_coders)
		{
			if (simu->coder[i].is_finished)
				return ;
		}

		
	}
	return (NULL);
}




void create_monitor(t_sumilation *simu)
{
	pthread_t	monitor;
	pthread_create(&monitor, NULL, monitor_routine, (void*)simu);

}

