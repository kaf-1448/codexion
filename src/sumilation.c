#include    "../library/codexion.h"


void	*routine(void	*args)
{
	t_coder *coder = (t_coder*)args;
	// int i;
	// i = 0;

	while (coder->compiles_count < coder->data->number_of_compiles_required)
	{
		pthread_mutex_lock(&coder->left_dongle->lock);
		pthread_mutex_lock(&coder->right_dongle->lock);

		printf("%d has taken a dongle \n", coder->id);
		printf("%d has taken a dongle \n", coder->id);
		printf("%d is compiling\n", coder->id);
		coder->compiles_count++;
		pthread_mutex_unlock(&coder->left_dongle->lock);
		pthread_mutex_unlock(&coder->right_dongle->lock);
	}
	
	
	return (NULL);
}


void	sumilation(t_sumilation *sum)
{
	int	i;

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_mutex_init(&sum->coder[i].left_dongle->lock, NULL);
		pthread_mutex_init(&sum->coder[i].right_dongle->lock, NULL);
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
