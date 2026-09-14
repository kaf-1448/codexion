/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:26:52 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/13 10:27:24 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../library/codexion.h"

void	clean_up_all(t_sumilation *simu)
{
	int	i;

	if (!simu)
		return ;
	i = 0;
	while (i < simu->data->number_of_coders)
	{
		pthread_mutex_destroy(&simu->dongle[i].lock);
		pthread_mutex_destroy(&simu->coder[i].coder_lock);
		pthread_cond_destroy(&simu->dongle[i].cond);
		if (simu->dongle[i].queue)
			free(simu->dongle[i].queue);
		i++;
	}
	pthread_mutex_destroy(&simu->print_lock);
	pthread_mutex_destroy(&simu->state_lock);
	free(simu->coder);
	free(simu->data);
	free(simu->dongle);
	free(simu);
}

int	main(int ac, char **ar)
{
	t_sumilation	*sum;

	if (ft_parsing(ac, ar))
		return (1);
	sum = intit_sumlation (ar);
	sumilation(sum);
	clean_up_all(sum);
	return (0);
}
