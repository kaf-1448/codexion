#include	"../library/codexion.h"

void	organize_queue(t_dongle *dongle, t_coder *coder)
{
	if (dongle->queue == NULL)
		return;

	if (dongle->queue->coders[0] == NULL)
		dongle->queue->coders[0] = coder;
	else if (dongle->queue->coders[1] == NULL)
		dongle->queue->coders[1] = coder;
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