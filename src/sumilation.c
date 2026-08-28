#include    "../library/codexion.h"

void	*routine(void	*args)
{
	t_coder *coder;
	t_dongle *first_dongle;
	t_dongle *second_dongle;

	coder = (t_coder*)args;
	
	
	if (coder->right_dongle->id < coder->left_dongle->id)
	{
		first_dongle = coder->right_dongle;
		second_dongle = coder->left_dongle;
	}
	else
	{
		first_dongle = coder->left_dongle;
		second_dongle = coder->right_dongle;
	}
	if (coder->id % 2 == 0)
		usleep(1000);

	while (coder->compiles_count < coder->data->number_of_compiles_required)
	{
		// if takedingle:
		// 	return 0;
		coder->left_dongle = first_dongle;
		coder->right_dongle = second_dongle;
		if (take_dongle(coder))
		{
		
			
			// 3. Update Last Compilation Time & Print Compiling
			pthread_mutex_lock(&coder->coder_lock);
			coder->last_time_compilation = get_time_of_ms();
			pthread_mutex_unlock(&coder->coder_lock);
	
			pthread_mutex_lock(&coder->simu->print_lock);
			printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
			pthread_mutex_unlock(&coder->simu->print_lock);
	
			// 4. Sleep for Compile Time (Holding Dongles)
			// ft_usleep(coder->simu, coder->simu->data->time_to_compile);
			
			pthread_mutex_lock(&coder->coder_lock);
			coder->compiles_count++;
			pthread_mutex_unlock(&coder->coder_lock);
			// if take:
			// 	takeoff

			// dubeg
			pthread_mutex_lock(&coder->simu->print_lock);
			printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
			pthread_mutex_unlock(&coder->simu->print_lock);
			usleep(coder->data->time_to_debug * 1000);
			ft_usleep(coder->simu, coder->simu->data->time_to_debug);
	
			
			// 5. Unlock Dongles
			// take_off_dongle(f);
			usleep(coder->data->dongle_cooldown * 1000);
			coder->left_dongle->is_free = 1;
			coder->right_dongle->is_free = 1;

			// 6. Debugging Phase
			// 7. Refactoring Phase
			pthread_mutex_lock(&coder->simu->print_lock);
			printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
			pthread_mutex_unlock(&coder->simu->print_lock);
			ft_usleep(coder->simu, coder->simu->data->time_to_refactor);
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

	init_mutex_dongle(sum);
	pthread_mutex_init(&sum->state_lock, NULL);
	pthread_mutex_init(&sum->print_lock, NULL);
	sum->start_time = get_time_of_ms();
	create_coders(sum);
	pthread_mutex_init(&sum->state_lock, NULL);

}
