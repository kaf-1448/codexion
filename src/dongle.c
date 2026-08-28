#include	"../library/codexion.h"

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


int take_dongle(t_coder *coder)
{
	if (!coder->left_dongle->is_free
		 && !coder->right_dongle->is_free
		&& coder->simu->is_simulation_over)
		return (0);

	pthread_mutex_lock(&coder->left_dongle->lock);
	pthread_mutex_lock(&coder->simu->print_lock);
	coder->left_dongle->is_free = 0;
	printf("%ld %d has taken a dongle\n",
		get_time_of_ms() - coder->simu->start_time, coder->id);
	printf("%ld %d has taken a dongle\n",
		get_time_of_ms() - coder->simu->start_time, coder->id);
	pthread_mutex_unlock(&coder->simu->print_lock);
	
	// pthread_mutex_lock(&coder->right_dongle->lock);
	// pthread_mutex_lock(&coder->simu->print_lock);
	coder->right_dongle->is_free = 0;
		// pthread_mutex_unlock(&coder->simu->print_lock);
	pthread_mutex_unlock(&coder->left_dongle->lock);
	pthread_mutex_unlock(&coder->right_dongle->lock);

	return (1);
}

// int	take_dongle(t_coder *coder, t_dongle *first, t_dongle *second)
// {
// 	pthread_mutex_lock(&first->lock);
// 	pthread_mutex_lock(&coder->simu->print_lock);
// 	printf("%ld %d has taken a dongle\n",
// 		get_time_of_ms() - coder->simu->start_time, coder->id);
// 	pthread_mutex_unlock(&coder->simu->print_lock);

// 	pthread_mutex_lock(&second->lock);
// 	pthread_mutex_lock(&coder->simu->print_lock);
// 	printf("%ld %d has taken a dongle\n",
// 		get_time_of_ms() - coder->simu->start_time, coder->id);
// 	pthread_mutex_unlock(&coder->simu->print_lock);
// 	return (0);
// }


// void take_off_dongle(t_dongle *first, t_dongle *second)
// {
// 	pthread_mutex_unlock(&first->lock);
// 	pthread_mutex_unlock(&second->lock);
// }

void take_off_dongle(t_dongle *first, t_dongle *second)
{
	first->is_free = 1;
	second->is_free = 1;
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&second->lock);
}

