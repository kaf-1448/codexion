/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:27:45 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/13 10:42:49 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../library/codexion.h"

static void	handle_burnout(t_sumilation *simu, int i, long current_time)
{
	int	j;

	pthread_mutex_lock(&simu->state_lock);
	pthread_mutex_lock(&simu->print_lock);
	printf("%ld %d burned out\n", current_time - simu->start_time, \
		simu->coder[i].id);
	simu->is_simulation_over = 1;
	j = 0;
	while (j < simu->data->number_of_coders)
	{
		pthread_cond_broadcast(&simu->dongle[j].cond);
		j++;
	}
	pthread_mutex_unlock(&simu->print_lock);
	pthread_mutex_unlock(&simu->state_lock);
}

static int	check_coder_burnout(t_sumilation *simu, int i)
{
	long	current_time;
	long	last_compile;

	current_time = get_time_of_ms();
	pthread_mutex_lock(&simu->coder[i].coder_lock);
	last_compile = simu->coder[i].last_time_compilation;
	pthread_mutex_unlock(&simu->coder[i].coder_lock);
	if (current_time - last_compile > simu->data->time_to_burnout)
	{
		pthread_mutex_lock(&simu->coder[i].coder_lock);
		if (simu->coder[i].is_finished == 1)
		{
			pthread_mutex_unlock(&simu->coder[i].coder_lock);
			return (0);
		}
		pthread_mutex_unlock(&simu->coder[i].coder_lock);
		handle_burnout(simu, i, current_time);
		return (1);
	}
	return (0);
}

static void	*monitor_routine(void *args)
{
	int				i;
	int				count;
	t_sumilation	*simu;

	simu = (t_sumilation *)args;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < simu->data->number_of_coders)
		{
			pthread_mutex_lock(&simu->coder[i].coder_lock);
			if (simu->coder[i].is_finished == 1)
				count++;
			pthread_mutex_unlock(&simu->coder[i].coder_lock);
			if (count == simu->data->number_of_coders)
				return (NULL);
			if (check_coder_burnout(simu, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	create_monitor(t_sumilation *simu)
{
	pthread_create(&simu->monitor_id, NULL, monitor_routine, (void *)simu);
}
