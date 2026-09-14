/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:27:51 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/13 10:29:48 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../library/codexion.h"

void	swap(t_coder **a, t_coder **b)
{
	t_coder	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	is_heigher_preoirity(t_coder *c1, t_coder *c2)
{
	long	d1;
	long	d2;

	d1 = c1->last_time_compilation + c1->data->time_to_burnout;
	d2 = c2->last_time_compilation + c2->data->time_to_burnout;
	if (c1->data->scheduler == 1)
		return (0);
	if (d1 < d2)
		return (1);
	else if (d1 == d2 && c1->id < c2->id)
		return (1);
	return (0);
}

void	heapify(t_dongle *dongle, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (is_heigher_preoirity(dongle->queue->coders[index],
				dongle->queue->coders[parent]))
		{
			swap(&dongle->queue->coders[index], &dongle->queue->coders[parent]);
			index = parent;
		}
		else
			break ;
	}
}

void	organize_queue(t_dongle *dongle, t_coder *coder)
{
	if (!dongle || dongle->queue == NULL || !coder)
		return ;
	if (dongle->queue->coders[0] == NULL)
		dongle->queue->coders[0] = coder;
	else if (dongle->queue->coders[1] == NULL)
	{
		dongle->queue->coders[1] = coder;
		heapify(dongle, 1);
	}
}

void	remove_from_queue(t_dongle *dongle, t_coder *coder)
{
	if (!dongle->queue || dongle->queue == NULL || !coder)
		return ;
	if (dongle->queue->coders[0] == coder)
	{
		dongle->queue->coders[0] = dongle->queue->coders[1];
		dongle->queue->coders[1] = NULL;
	}
	else if (dongle->queue->coders[1] == coder)
		dongle->queue->coders[1] = NULL;
}
