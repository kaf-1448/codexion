/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:25:57 by ykaf              #+#    #+#             */
/*   Updated: 2026/10/09 10:47:14 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../library/codexion.h"

void	init_mutex_dongle(t_sumilation *sum)
{
	int	i;

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_mutex_init(&sum->dongle[i].lock, NULL);
		pthread_mutex_init(&sum->coder[i].coder_lock, NULL);
		pthread_cond_init(&sum->dongle[i].cond, NULL);
		i++;
	}
}

static void	check_call_dawn(t_dongle *dongle, long call_down)
{
	long	target;

	target = dongle->avaibale_at + call_down;
	while (get_time_of_ms() < target)
		usleep(200);
}

static int	wait_for_dongle(t_coder *coder, t_dongle *dongle)
{
	t_coder	*other;

	other = get_other_coder(coder, dongle);
	while (dongle->is_free == 0 || dongle->queue->coders[0] != coder \
		|| (coder->data->scheduler == 2 && !other->is_finished \
			&& other->last_time_compilation < coder->last_time_compilation) \
		|| (coder->data->scheduler == 1 && !other->is_finished \
			&& other->time_to_request != 0 \
			&& other->time_to_request < coder->time_to_request))
	{
		pthread_mutex_lock(&coder->simu->state_lock);
		if (coder->simu->is_simulation_over)
			return (pthread_mutex_unlock(&dongle->lock),
				pthread_mutex_unlock(&coder->simu->state_lock), 0);
		pthread_mutex_unlock(&coder->simu->state_lock);
		pthread_cond_wait(&dongle->cond, &dongle->lock);
		pthread_mutex_lock(&coder->simu->state_lock);
		if (coder->simu->is_simulation_over)
			return (pthread_mutex_unlock(&dongle->lock),
				pthread_mutex_unlock(&coder->simu->state_lock), 0);
		pthread_mutex_unlock(&coder->simu->state_lock);
	}
	return (1);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	organize_queue(dongle, coder);
	if (!wait_for_dongle(coder, dongle))
		return (0);
	check_call_dawn(dongle, coder->data->dongle_cooldown);
	pthread_mutex_lock(&coder->simu->state_lock);
	if (coder->simu->is_simulation_over)
		return (pthread_mutex_unlock(&dongle->lock), \
			pthread_mutex_unlock(&coder->simu->state_lock), 0);
	pthread_mutex_unlock(&coder->simu->state_lock);
	dongle->is_free = 0;
	remove_from_queue(dongle, coder);
	pthread_mutex_unlock(&dongle->lock);
	return (1);
}

void	take_off_dongle(t_dongle *dongle)
{	
	pthread_mutex_lock(&dongle->lock);
	dongle->is_free = 1;
	dongle->avaibale_at = get_time_of_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}
