#include	"../library/codexion.h"
#include <unistd.h>


static void	edf_algorithm(t_dongle *dongle, t_coder *coder)
{
	long	deadline_new;
	long	deadline_old;
	t_coder	*temp;

	deadline_new = coder->data->time_to_burnout + coder->last_time_compilation;
	if (dongle->queue->coders[0] == NULL)
		dongle->queue->coders[0] = coder;
	else if (dongle->queue->coders[1] == NULL)
	{
		temp = dongle->queue->coders[0];
		deadline_old = temp->data->time_to_burnout + temp->last_time_compilation;
		if (deadline_new < deadline_old )
		{
			dongle->queue->coders[0] = coder;
			dongle->queue->coders[1]= temp;
		}
		else if (deadline_new == deadline_old && coder->id < temp->id)
		{
			dongle->queue->coders[0] = coder;
			dongle->queue->coders[1]= temp;
		}
		else
			dongle->queue->coders[1]= coder;
	}
}


void	organize_queue(t_dongle *dongle, t_coder *coder)
{
	if (dongle->queue == NULL)
		return;
	if (coder->data->scheduler == 1)
	{
		if (dongle->queue->coders[0] == NULL)
			dongle->queue->coders[0] = coder;
		else if (dongle->queue->coders[1] == NULL)
			dongle->queue->coders[1] = coder;
	}
	else if (coder->data->scheduler == 2)
	{
		edf_algorithm(dongle, coder);
	}
}

void	remove_from_queue(t_dongle *dongle, t_coder *coder)
{
	if (!dongle->queue)
		return ;
	if (dongle->queue->coders[0] == coder)
		dongle->queue->coders[0] = dongle->queue->coders[1];
	else if (dongle->queue->coders[1] == coder)
		dongle->queue->coders[1] = NULL;
}
