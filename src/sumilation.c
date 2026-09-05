#include    "../library/codexion.h"
#include <pthread.h>
#include <unistd.h>


void	*routine(void *args)
{
	t_dongle	*first_d;
	t_dongle	*second_d;
	t_coder	*coder = (t_coder*)args;

	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		first_d = coder->left_dongle; 
		second_d = coder->right_dongle; 
	}
	else
	{
		first_d = coder->right_dongle; 
		second_d = coder->left_dongle; 
	}
	if (coder->id % 2 == 0)
		usleep(1000);

	while (1)
	{
		pthread_mutex_lock(&coder->coder_lock);
		if (coder->compiles_count == coder->data->number_of_compiles_required)
		{
			coder->is_finished = 1;
			pthread_mutex_unlock(&coder->coder_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&coder->coder_lock);

		pthread_mutex_lock(&coder->simu->state_lock);
		if (coder->simu->is_simulation_over)
		{
			pthread_mutex_unlock(&coder->simu->state_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&coder->simu->state_lock);


		if (take_dongle(coder, first_d) && take_dongle(coder, second_d) )
		{
			// compilation
			pthread_mutex_lock(&coder->simu->state_lock);
			if (coder->simu->is_simulation_over)
			{
				pthread_mutex_unlock(&coder->simu->state_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&coder->simu->state_lock);
			pthread_mutex_lock(&coder->coder_lock);
			printf("%ld %d is compiling\n", get_time_of_ms()  - coder->simu->start_time, coder->id);      //c
			pthread_mutex_unlock(&coder->coder_lock);
			// update time of last compile
			pthread_mutex_lock(&coder->coder_lock);
			coder->last_time_compilation = get_time_of_ms();
			pthread_mutex_unlock(&coder->coder_lock);
			if (ft_usleep(coder->simu, coder->data->time_to_compile))
			{
				take_off_dongle(first_d);
				take_off_dongle(second_d);
				return (NULL);
			}

			// call down
			
			pthread_mutex_lock(&coder->simu->state_lock);
			if (coder->simu->is_simulation_over)
			{
				pthread_mutex_unlock(&coder->simu->state_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&coder->simu->state_lock);
			take_off_dongle(first_d);
			take_off_dongle(second_d);
			// usleep(coder->data->dongle_cooldown * 1000);
			

			// count compile required
			pthread_mutex_lock(&coder->coder_lock);
			coder->compiles_count++;
			pthread_mutex_unlock(&coder->coder_lock);

			// debuging
			pthread_mutex_lock(&coder->simu->state_lock);
			if (coder->simu->is_simulation_over)
			{
				pthread_mutex_unlock(&coder->simu->state_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&coder->simu->state_lock);
			pthread_mutex_lock(&coder->coder_lock);
			printf("%ld %d is debugging\n", get_time_of_ms()  - coder->simu->start_time, coder->id);  //d
			pthread_mutex_unlock(&coder->coder_lock);
			// usleep(coder->data->time_to_debug *1000);
			if (ft_usleep(coder->simu, coder->data->time_to_debug))
			{
				return (NULL);
			}
			
			
			// refactoring
			pthread_mutex_lock(&coder->simu->state_lock);
			if (coder->simu->is_simulation_over)
			{
				pthread_mutex_unlock(&coder->simu->state_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&coder->simu->state_lock);
			pthread_mutex_lock(&coder->coder_lock);
			printf("%ld %d is refactoring\n", get_time_of_ms()  - coder->simu->start_time, coder->id);  //r
			pthread_mutex_unlock(&coder->coder_lock);
			if (ft_usleep(coder->simu, coder->data->time_to_refactor))
			{
				return (NULL);
			}
		}

	}
	

    return (NULL);
}


static int	create_coders(t_sumilation *sum)
{
	int	i;

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_create(&sum->coder[i].thread_id, NULL, routine, (void *)&sum->coder[i]);
		i++;
	}
	create_monitor(sum);
	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_join(sum->coder[i].thread_id, NULL);
		i++;
	}
	return (1);
}

void	sumilation(t_sumilation *sum)
{
	int i;

	init_mutex_dongle(sum);
	pthread_mutex_init(&sum->state_lock, NULL);
	pthread_mutex_init(&sum->print_lock, NULL);
	sum->start_time = get_time_of_ms();

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		sum->coder[i].last_time_compilation = sum->start_time;
		i++;
	}
	create_coders(sum);
	pthread_join(sum->monitor_id, NULL);
}
