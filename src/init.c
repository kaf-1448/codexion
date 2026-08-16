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
