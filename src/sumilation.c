#include    "../library/codexion.h"


// void	*routine(void	*args)
// {
// 	t_coder *coder;
// 	t_dongle *first_dongle;
// 	t_dongle *second_dongle;

// 	coder = (t_coder*)args;
	
	
// 	if (coder->right_dongle->id < coder->left_dongle->id)
// 	{
// 		first_dongle = coder->right_dongle;
// 		second_dongle = coder->left_dongle;
// 	}
// 	else
// 	{
// 		first_dongle = coder->left_dongle;
// 		second_dongle = coder->right_dongle;
// 	}

// 	while (coder->compiles_count < coder->data->number_of_compiles_required)
// 	{
// 		pthread_mutex_lock(&coder->simu->print_lock);

// 		pthread_mutex_lock(&first_dongle->lock);
// 		pthread_mutex_lock(&second_dongle->lock);
// 		printf("%d has taken a dongle\n", coder->id);
		
// 		printf("%d has taken a dongle\n", coder->id);
		
// 		printf("%d is compiling\n", coder->id);
// 		pthread_mutex_unlock(&coder->simu->print_lock);
		
// 		pthread_mutex_lock(&coder->coder_lock);
// 		coder->compiles_count++;
// 		pthread_mutex_unlock(&coder->coder_lock);

		
		
// 		pthread_mutex_unlock(&first_dongle->lock);
// 		pthread_mutex_unlock(&second_dongle->lock);

// 	}
	
	
	
// 	return (NULL);
// }



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

	while (coder->compiles_count < coder->data->number_of_compiles_required)
	{
		take_dongle(coder, first_dongle, second_dongle);

		// 3. Update Last Compilation Time & Print Compiling
		pthread_mutex_lock(&coder->coder_lock);
		coder->last_time_compilation = get_time_of_ms();
		pthread_mutex_unlock(&coder->coder_lock);

		pthread_mutex_lock(&coder->simu->print_lock);
		printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
		pthread_mutex_unlock(&coder->simu->print_lock);

		// 4. Sleep for Compile Time (Holding Dongles)
		ft_usleep(coder->simu, coder->simu->data->time_to_compile);

		pthread_mutex_lock(&coder->coder_lock);
		coder->compiles_count++;
		pthread_mutex_unlock(&coder->coder_lock);

		// 5. Unlock Dongles
		take_off_dongle(first_dongle, second_dongle);
		// 6. Debugging Phase
		pthread_mutex_lock(&coder->simu->print_lock);
		printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
		pthread_mutex_unlock(&coder->simu->print_lock);
		ft_usleep(coder->simu, coder->simu->data->time_to_debug);

		// 7. Refactoring Phase
		pthread_mutex_lock(&coder->simu->print_lock);
		printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
		pthread_mutex_unlock(&coder->simu->print_lock);
		ft_usleep(coder->simu, coder->simu->data->time_to_refactor);

	}
	
	
	return (NULL);
}

void	sumilation(t_sumilation *sum)
{
	int	i;
	
	i = 0;
	init_mutex_dongle(sum);
	pthread_mutex_init(&sum->print_lock, NULL);
	sum->start_time = get_time_of_ms();
	while (i < sum->data->number_of_coders)
	{
		pthread_create(&sum->coder[i].thread_id, NULL, routine, (void*)&sum->coder[i]);
		i++;
	}

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_join(sum->coder[i].thread_id, NULL);
		i++;
	}
}
