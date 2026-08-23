#include    "../library/codexion.h"

t_data *intilize_data(char **ar)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->number_of_coders = ft_atoi(ar[1]);
	data->time_to_burnout = ft_atoi(ar[2]);
	data->time_to_compile = ft_atoi(ar[3]);
	data->time_to_debug = ft_atoi(ar[4]);
	data->time_to_refactor = ft_atoi(ar[5]);
	data->number_of_compiles_required = ft_atoi(ar[6]);
	data->dongle_cooldown = ft_atoi(ar[7]);
	if (strcmp("fifo", ar[8]) == 0)
		data->scheduler = 1;
	else
		data->scheduler = 2;
	return (data);
}

t_dongle	*create_dongles(t_data *data)
{
	t_dongle	*dongle;
	int i;
	
	dongle = malloc(sizeof(t_dongle) * data->number_of_coders);
	if (!dongle)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		dongle[i].id = i+1;
		dongle[i].is_free = 1;
		dongle[i].last_released_time = 0;
		pthread_mutex_init(&dongle[i].lock, NULL);
		i++;
	}
	return (dongle);
}

t_coder *create_coders(t_data *data, t_dongle *dongle, t_sumilation *simu)
{
	t_coder *coders;
	// struct timeval tv;
	int	i;
	
	coders = malloc(sizeof(t_coder) * data->number_of_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < data->number_of_coders)
	{
		coders[i].id = i+1;
		coders[i].last_time_compilation = 0;
		coders[i].compiles_count = 0;
		coders[i].is_finished = 0;
		coders[i].right_dongle = &dongle[(i -1 + data->number_of_coders) % data->number_of_coders];
		coders[i].left_dongle = &dongle[i];
		coders[i].data = data;
		coders[i].simu = simu;
		i++;
	}
	return (coders);
}


t_sumilation *intit_sumlation(char **ar)
{
	t_sumilation	*sum;

	sum = malloc(sizeof(t_sumilation ));
	if (!sum)
		return (NULL);
	sum->data = intilize_data(ar);
	if (!sum->data)
		return (free(sum), NULL);
	sum->dongle = create_dongles(sum->data);
	if (!sum->dongle)
		return (free(sum->data), free(sum), NULL);
	sum->coder = create_coders(sum->data,sum->dongle, sum);
	if (!sum->coder)
		return (free(sum->dongle),free(sum->data), free(sum), NULL);
	return (sum);
}

