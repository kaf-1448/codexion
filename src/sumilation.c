/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumilation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykaf <ykaf@student.1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:22:58 by ykaf              #+#    #+#             */
/*   Updated: 2026/09/06 17:52:59 by ykaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../library/codexion.h"

static int	only_coder(t_coder *coder, t_dongle *dongle)
{
	if (coder->data->number_of_coders == 1)
	{
		take_dongle(coder ,dongle);
		take_off_dongle(dongle);
		return (1);
	}
	return (0);
}

static void	init_dongles_order(t_coder *coder, t_dongle **d1, t_dongle **d2)
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





static int	do_compile(t_coder *coder, t_dongle *d1, t_dongle *d2)
{
	// print_state_dongle(coder);
	pthread_mutex_lock(&coder->simu->print_lock);
	// if (coder->left_dongle->is_free == 0 && coder->right_dongle->is_free == 0)
	// {
	printf("%ld %d has taken a dongle\n", \
	get_time_of_ms() - coder->simu->start_time, coder->id);
	printf("%ld %d has taken a dongle\n", \
	get_time_of_ms() - coder->simu->start_time, coder->id);
	// }
	printf("%ld %d is compiling\n", \
		get_time_of_ms() - coder->simu->start_time, coder->id);
	pthread_mutex_unlock(&coder->simu->print_lock);
	pthread_mutex_lock(&coder->coder_lock);
	coder->last_time_compilation = get_time_of_ms();
	pthread_mutex_unlock(&coder->coder_lock);
	if (ft_usleep(coder->simu, coder->data->time_to_compile))
	{
		take_off_dongle(d1);
		take_off_dongle(d2);
		return (1);
	}
	take_off_dongle(d1);
	take_off_dongle(d2);
	pthread_mutex_lock(&coder->coder_lock);
	coder->compiles_count++;
	pthread_mutex_unlock(&coder->coder_lock);
	return (0);
}

static int	do_debug_refactor(t_coder *coder)
{
	pthread_mutex_lock(&coder->simu->print_lock);
	printf("%ld %d is debugging\n", \
		get_time_of_ms() - coder->simu->start_time, coder->id);
	pthread_mutex_unlock(&coder->simu->print_lock);
	if (ft_usleep(coder->simu, coder->data->time_to_debug))
		return (1);
	pthread_mutex_lock(&coder->simu->print_lock);
	printf("%ld %d is refactoring\n", \
		get_time_of_ms() - coder->simu->start_time, coder->id);
	pthread_mutex_unlock(&coder->simu->print_lock);
	if (ft_usleep(coder->simu, coder->data->time_to_refactor))
		return (1);
	if (coder->data->dongle_cooldown > (coder->data->time_to_compile + \
		coder->data->time_to_debug + coder->data->time_to_refactor) \
		&& coder->data->number_of_coders % 2 != 0 \
		&& coder->compiles_count < coder->data->number_of_compiles_required)
		usleep(coder->data->dongle_cooldown * 2 * 1000);
	else
		usleep(1000);
	return (0);
}



void	*routine(void *args)
{
	t_dongle	*first_d;
	t_dongle	*second_d;
	t_coder		*coder;

	coder = (t_coder *)args;
	init_dongles_order(coder, &first_d, &second_d);
	while (1)
	{
		if (only_coder(coder, first_d))
			return (NULL);
		pthread_mutex_lock(&coder->coder_lock);
		if (coder->compiles_count == coder->data->number_of_compiles_required)
		{
			coder->is_finished = 1;
			return (pthread_mutex_unlock(&coder->coder_lock), NULL);
		}
		pthread_mutex_unlock(&coder->coder_lock);
		if (!take_dongle(coder, first_d))
			return (NULL);
		if (!take_dongle(coder, second_d))
			return (take_off_dongle(first_d), NULL);
		if (do_compile(coder, first_d, second_d) || do_debug_refactor(coder))
			return (NULL);
	}
	return (NULL);
}

static int	create_coders(t_sumilation *sum)
{
	int	i;

	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_create(&sum->coder[i].thread_id, \
		NULL, routine, (void *)&sum->coder[i]);
		i++;
	}
	create_monitor(sum);
	i = 0;
	while (i < sum->data->number_of_coders)
	{
		pthread_join(sum->coder[i].thread_id, NULL);
		i++;
	}
	return (1);
}

void	sumilation(t_sumilation *sum)
{
	int	i;

	init_mutex_dongle(sum);
	pthread_mutex_init(&sum->state_lock, NULL);
	pthread_mutex_init(&sum->print_lock, NULL);
	sum->start_time = get_time_of_ms();
	i = 0;
	while (i < sum->data->number_of_coders)
	{
		sum->coder[i].last_time_compilation = sum->start_time;
		i++;
	}
	create_coders(sum);
	pthread_join(sum->monitor_id, NULL);
}

// void	*routine(void *args)
// {
// 	t_dongle	*first_d;
// 	t_dongle	*second_d;
// 	t_coder		*coder;

// 	coder = (t_coder *)args;
// 	if (coder->left_dongle->id < coder->right_dongle->id)
// 	{
// 		first_d = coder->left_dongle;
// 		second_d = coder->right_dongle;
// 	}
// 	else
// 	{
// 		first_d = coder->right_dongle;
// 		second_d = coder->left_dongle;
// 	}
// 	if (coder->id % 2 == 0)
// 		usleep(1000);
	
// 	while (1)
// 	{
// 		if (only_coder(coder, first_d))
// 			return (NULL);
// 		pthread_mutex_lock(&coder->coder_lock);
// 		if (coder->compiles_count == coder->data->number_of_compiles_required)
// 		{
// 			coder->is_finished = 1;
// 			pthread_mutex_unlock(&coder->coder_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->coder_lock);
// 		pthread_mutex_lock(&coder->simu->state_lock);
// 		if (coder->simu->is_simulation_over)
// 		{
// 			pthread_mutex_unlock(&coder->simu->state_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->simu->state_lock);
// 		// if (take_dongle(coder, first_d) && take_dongle(coder, second_d))
// 		// {
// 		if (!take_dongle(coder, first_d))
// 			return (NULL);
// 		if (!take_dongle(coder, second_d))
// 		{
// 			take_off_dongle(first_d);
// 			return (NULL);
// 		}
// 		pthread_mutex_lock(&coder->simu->state_lock);
// 		if (coder->simu->is_simulation_over)
// 		{
// 			take_off_dongle(first_d);
// 			take_off_dongle(second_d);
// 			pthread_mutex_unlock(&coder->simu->state_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->simu->state_lock);
// 		pthread_mutex_lock(&coder->simu->print_lock);
// 		printf("%ld %d is compiling\n", 
// 		get_time_of_ms() - coder->simu->start_time, coder->id);
// 		pthread_mutex_unlock(&coder->simu->print_lock);
// 		pthread_mutex_lock(&coder->coder_lock);
// 		coder->last_time_compilation = get_time_of_ms();
// 		pthread_mutex_unlock(&coder->coder_lock);
// 		if (ft_usleep(coder->simu, coder->data->time_to_compile))
// 		{
// 			take_off_dongle(first_d);
// 			take_off_dongle(second_d);
// 			return (NULL);
// 		}
// 		pthread_mutex_lock(&coder->simu->state_lock);
// 		if (coder->simu->is_simulation_over)
// 		{
// 			take_off_dongle(first_d);
// 			take_off_dongle(second_d);
// 			pthread_mutex_unlock(&coder->simu->state_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->simu->state_lock);
// 		take_off_dongle(first_d);
// 		take_off_dongle(second_d);
// 		pthread_mutex_lock(&coder->coder_lock);
// 		coder->compiles_count++;
// 		pthread_mutex_unlock(&coder->coder_lock);
// 		pthread_mutex_lock(&coder->simu->state_lock);
// 		if (coder->simu->is_simulation_over)
// 		{
// 			pthread_mutex_unlock(&coder->simu->state_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->simu->state_lock);
// 		pthread_mutex_lock(&coder->simu->print_lock);
// 		printf("%ld %d is debugging\n", 
// 		get_time_of_ms() - coder->simu->start_time, coder->id);
// 		pthread_mutex_unlock(&coder->simu->print_lock);
// 		if (ft_usleep(coder->simu, coder->data->time_to_debug))
// 		{
// 			return (NULL);
// 		}
// 		pthread_mutex_lock(&coder->simu->state_lock);
// 		if (coder->simu->is_simulation_over)
// 		{
// 			pthread_mutex_unlock(&coder->simu->state_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&coder->simu->state_lock);
// 		pthread_mutex_lock(&coder->simu->print_lock);
// 		printf("%ld %d is refactoring\n", 
// 		get_time_of_ms() - coder->simu->start_time, coder->id);
// 		pthread_mutex_unlock(&coder->simu->print_lock);
// 		if (ft_usleep(coder->simu, coder->data->time_to_refactor))
// 		{
// 			return (NULL);
// 		}
// 		if (coder->data->dongle_cooldown > (coder->data->time_to_compile + 
// 			coder->data->time_to_debug + coder->data->time_to_refactor) 
			// && coder->data->number_of_coders % 2 != 0 
// 			&& coder->compiles_count < coder->data->number_of_compiles_required)
// 			usleep(coder->data->dongle_cooldown * 2 * 1000);
// 		else 
// 		{
// 			usleep(1000);
// 		}
		
		
// 	}
// 	return (NULL);
// }
