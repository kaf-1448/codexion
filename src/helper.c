/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:41:08 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/13 10:44:24 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/codexion.h"

int	only_coder(t_coder *coder, t_dongle *dongle)
{
	if (coder->data->number_of_coders == 1)
	{
		take_dongle (coder, dongle);
		pthread_mutex_lock(&coder->simu->print_lock);
		printf("%ld %d has taken a dongle\n", \
		get_time_of_ms() - coder->simu->start_time, coder->id);
		pthread_mutex_unlock(&coder->simu->print_lock);
		take_off_dongle(dongle);
		return (1);
	}
	return (0);
}

void	init_dongles_order(t_coder *coder, t_dongle **d1, t_dongle **d2)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*d1 = coder->left_dongle;
		*d2 = coder->right_dongle;
	}
	else
	{
		*d1 = coder->right_dongle;
		*d2 = coder->left_dongle;
	}
	if (coder->id % 2 == 0)
		usleep(1000);
}
