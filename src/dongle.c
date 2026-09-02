#include	"../library/codexion.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void	init_mutex_dongle(t_sumilation *sum)
{
	int	i;

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_mutex_init(&sum->dongle[i].lock, NULL);
		pthread_mutex_init(&sum->coder[i].coder_lock, NULL);
		i++;
	}
}


int take_dongle(t_coder *coder, t_dongle *dongle)
{

	pthread_mutex_lock(&coder->simu->state_lock);
	if (coder->simu->is_simulation_over)
	{
		pthread_mutex_unlock(&coder->simu->state_lock);
		return (0);
	}
	pthread_mutex_unlock(&coder->simu->state_lock);
	
	pthread_mutex_lock(&dongle->lock);
	organize_queue(dongle, coder);
	
	while (dongle->is_free == 0 || dongle->queue->coders[0] != coder)
{
		pthread_mutex_lock(&coder->simu->state_lock);
		if (coder->simu->is_simulation_over)
		{
			pthread_mutex_unlock(&coder->simu->state_lock);
			return (0);
		}
		pthread_mutex_unlock(&coder->simu->state_lock);

		pthread_cond_wait(&dongle->cond, &dongle->lock);

		pthread_mutex_lock(&coder->simu->state_lock);
		if (coder->simu->is_simulation_over)
		{
			pthread_mutex_unlock(&coder->simu->state_lock);
			return (0);
		}
		pthread_mutex_unlock(&coder->simu->state_lock);
	}

	dongle->is_free = 0;
	pthread_mutex_lock(&coder->simu->print_lock);
	printf("%ld %d is taken a dongle.\n", get_time_of_ms() - coder->simu->start_time, coder->id);
	pthread_mutex_unlock(&coder->simu->print_lock);
	
	remove_from_queue(dongle, coder);





    return (1);
}


void take_off_dongle(t_dongle *dongle)
{
	pthread_cond_broadcast(&dongle->cond);
	dongle->is_free = 1;
	pthread_mutex_unlock(&dongle->lock);
}

