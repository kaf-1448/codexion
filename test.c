// // #include    "../library/codexion.h"
// // #include <bits/pthreadtypes.h>

// // // void	*routine(void	*args)
// // // {
// // // 	t_coder *coder;
// // // 	t_dongle *first_dongle;
// // // 	t_dongle *second_dongle;

// // // 	coder = (t_coder*)args;
	
	
// // // 	if (coder->right_dongle->id < coder->left_dongle->id)
// // // 	{
// // // 		first_dongle = coder->right_dongle;
// // // 		second_dongle = coder->left_dongle;
// // // 	}
// // // 	else
// // // 	{
// // // 		first_dongle = coder->left_dongle;
// // // 		second_dongle = coder->right_dongle;
// // // 	}
// // // 	if (coder->id % 2 == 0)
// // // 		usleep(1000);


// // // 	while (!coder->simu->is_simulation_over)
// // // 	pthread_mutex_lock(&coder->simu->state_lock);
// // // 	{
// // // 		pthread_mutex_lock(&coder->coder_lock);
// // // 		if (coder->compiles_count == coder->data->number_of_compiles_required)
// // // 		{
// // // 			pthread_mutex_unlock(&coder->coder_lock);
// // // 			return (NULL);
// // // 		}
// // // 		pthread_mutex_unlock(&coder->coder_lock);
// // // 		usleep(1000);
		
		
// // // 		if (take_dongle(coder, first_dongle, second_dongle))
// // // 		{
			

// // // 			pthread_mutex_lock(&coder->coder_lock);
// // // 			coder->last_time_compilation = get_time_of_ms();
// // // 			pthread_mutex_unlock(&coder->coder_lock);
			
// // // 			if (!coder->simu->is_simulation_over)
// // // 			{
// // // 				pthread_mutex_lock(&coder->simu->print_lock);
// // // 				printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // // 				if (ft_usleep(coder->simu, coder->data->time_to_compile))
// // // 				{
// // // 					take_off_dongle(first_dongle, second_dongle);
// // // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // // 					return (NULL);
// // // 				}
// // // 				take_off_dongle(first_dongle, second_dongle);
		

// // // 				pthread_mutex_lock(&coder->coder_lock);
// // // 				coder->compiles_count++;
// // // 				pthread_mutex_unlock(&coder->coder_lock);

// // // 				pthread_mutex_lock(&coder->simu->print_lock);
// // // 				printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // // 				// ft_usleep(coder->simu, coder->simu->data->time_to_debug);
// // // 				if (ft_usleep(coder->simu, coder->data->time_to_debug))
// // // 				{
// // // 					take_off_dongle(first_dongle, second_dongle);
// // // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // // 					return (NULL);
// // // 				}


// // // 				pthread_mutex_lock(&coder->simu->print_lock);
// // // 				printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // // 				// ft_usleep(coder->simu, coder->simu->data->time_to_refactor);
// // // 				if (ft_usleep(coder->simu, coder->data->time_to_refactor))
// // // 				{
// // // 					take_off_dongle(first_dongle, second_dongle);
// // // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // // 					return (NULL);
// // // 				}
// // // 			}
// // // 			pthread_mutex_unlock(&coder->simu->state_lock);
// // // 		}
			
// // // 	}

	
	
	
// // // 	return (NULL);
// // // }

// // void *routine(void *args)
// // {
// //     t_coder *coder;
// //     t_dongle *first_dongle;
// //     t_dongle *second_dongle;

// //     coder = (t_coder*)args;
    
// //     // 1. ترتيب الوصلات لمنع الـ Deadlock
// //     if (coder->right_dongle->id < coder->left_dongle->id)
// //     {
// //         first_dongle = coder->right_dongle;
// //         second_dongle = coder->left_dongle;
// //     }
// //     else
// //     {
// //         first_dongle = coder->left_dongle;
// //         second_dongle = coder->right_dongle;
// //     }

// //     if (coder->id % 2 == 0)
// //         usleep(1000);

// //     while (1)
// //     {
// //         // فحص سريع وآمن لانتهاء المحاكاة (قفل ثم فتح فوراً)
// //         pthread_mutex_lock(&coder->simu->state_lock);
// //         if (coder->simu->is_simulation_over)
// //         {
// //             pthread_mutex_unlock(&coder->simu->state_lock);
// //             return (NULL);
// //         }
// //         pthread_mutex_unlock(&coder->simu->state_lock);

// //         // التحقق من عدد مرات التجميع المطلوبة
// //         pthread_mutex_lock(&coder->coder_lock);
// //         if (coder->compiles_count == coder->data->number_of_compiles_required)
// //         {
// //             pthread_mutex_unlock(&coder->coder_lock);
// //             return (NULL);
// //         }
// //         pthread_mutex_unlock(&coder->coder_lock);
// //         usleep(1000);
        
// //         // 2. أخذ الوصلات معاً
// //         if (take_dongle(coder, first_dongle, second_dongle))
// //         {
// //             // تحديث وقت آخر تجميع
// //             pthread_mutex_lock(&coder->coder_lock);
// //             coder->last_time_compilation = get_time_of_ms();
// //             pthread_mutex_unlock(&coder->coder_lock);

// //             // طباعة Compiling
// //             pthread_mutex_lock(&coder->simu->print_lock);
// //             printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// //             pthread_mutex_unlock(&coder->simu->print_lock);

// //             // النوم أثناء التجميع
// //             if (ft_usleep(coder->simu, coder->data->time_to_compile))
// //             {
// //                 take_off_dongle(first_dongle, second_dongle);
// //                 return (NULL);
// //             }

// //             // تحرير الوصلات فوراً بعد التجميع
// //             take_off_dongle(first_dongle, second_dongle);

// //             // زيادة عداد التجميع
// //             pthread_mutex_lock(&coder->coder_lock);
// //             coder->compiles_count++;
// //             pthread_mutex_unlock(&coder->coder_lock);

// //             // مرحلة التصحيح (Debugging)
// //             pthread_mutex_lock(&coder->simu->print_lock);
// //             printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// //             pthread_mutex_unlock(&coder->simu->print_lock);

// //             if (ft_usleep(coder->simu, coder->data->time_to_debug))
// //                 return (NULL);

// //             // مرحلة إعادة الهيكلة (Refactoring)
// //             pthread_mutex_lock(&coder->simu->print_lock);
// //             printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// //             pthread_mutex_unlock(&coder->simu->print_lock);

// //             if (ft_usleep(coder->simu, coder->data->time_to_refactor))
// //                 return (NULL);
// //         }
// //     }
// //     return (NULL);
// // }


// // static int	create_coders(t_sumilation *sum)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (i < sum->data->number_of_coders)
// // 	{
// // 		pthread_create(&sum->coder[i].thread_id, NULL, routine, (void *)&sum->coder[i]);
// // 		i++;
// // 	}
// // 	create_monitor(sum);
// // 	i = 0;
// // 	while (i < sum->data->number_of_coders)
// // 	{
// // 		pthread_join(sum->coder[i].thread_id, NULL);
// // 		i++;
// // 	}
// // 	return (1);
// // }

// // void	sumilation(t_sumilation *sum)
// // {

// // 	init_mutex_dongle(sum);
// // 	pthread_mutex_init(&sum->state_lock, NULL);
// // 	pthread_mutex_init(&sum->print_lock, NULL);
// // 	sum->start_time = get_time_of_ms();
// // 	create_coders(sum);
// // 	pthread_mutex_init(&sum->state_lock, NULL);
// // 	pthread_join(sum->monitor_id, NULL);
// // }


// //// second code

// #include    "../library/codexion.h"
// #include <bits/pthreadtypes.h>

// // void	*routine(void	*args)
// // {
// // 	t_coder *coder;
// // 	t_dongle *first_dongle;
// // 	t_dongle *second_dongle;

// // 	coder = (t_coder*)args;
	
	
// // 	if (coder->right_dongle->id < coder->left_dongle->id)
// // 	{
// // 		first_dongle = coder->right_dongle;
// // 		second_dongle = coder->left_dongle;
// // 	}
// // 	else
// // 	{
// // 		first_dongle = coder->left_dongle;
// // 		second_dongle = coder->right_dongle;
// // 	}
// // 	if (coder->id % 2 == 0)
// // 		usleep(1000);


// // 	while (!coder->simu->is_simulation_over)
// // 	pthread_mutex_lock(&coder->simu->state_lock);
// // 	{
// // 		pthread_mutex_lock(&coder->coder_lock);
// // 		if (coder->compiles_count == coder->data->number_of_compiles_required)
// // 		{
// // 			pthread_mutex_unlock(&coder->coder_lock);
// // 			return (NULL);
// // 		}
// // 		pthread_mutex_unlock(&coder->coder_lock);
// // 		usleep(1000);
		
		
// // 		if (take_dongle(coder, first_dongle, second_dongle))
// // 		{
			

// // 			pthread_mutex_lock(&coder->coder_lock);
// // 			coder->last_time_compilation = get_time_of_ms();
// // 			pthread_mutex_unlock(&coder->coder_lock);
			
// // 			if (!coder->simu->is_simulation_over)
// // 			{
// // 				pthread_mutex_lock(&coder->simu->print_lock);
// // 				printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // 				if (ft_usleep(coder->simu, coder->data->time_to_compile))
// // 				{
// // 					take_off_dongle(first_dongle, second_dongle);
// // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // 					return (NULL);
// // 				}
// // 				take_off_dongle(first_dongle, second_dongle);
		

// // 				pthread_mutex_lock(&coder->coder_lock);
// // 				coder->compiles_count++;
// // 				pthread_mutex_unlock(&coder->coder_lock);

// // 				pthread_mutex_lock(&coder->simu->print_lock);
// // 				printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // 				// ft_usleep(coder->simu, coder->simu->data->time_to_debug);
// // 				if (ft_usleep(coder->simu, coder->data->time_to_debug))
// // 				{
// // 					take_off_dongle(first_dongle, second_dongle);
// // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // 					return (NULL);
// // 				}


// // 				pthread_mutex_lock(&coder->simu->print_lock);
// // 				printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
// // 				pthread_mutex_unlock(&coder->simu->print_lock);
// // 				// ft_usleep(coder->simu, coder->simu->data->time_to_refactor);
// // 				if (ft_usleep(coder->simu, coder->data->time_to_refactor))
// // 				{
// // 					take_off_dongle(first_dongle, second_dongle);
// // 					// pthread_mutex_unlock(&coder->simu->state_lock);
// // 					return (NULL);
// // 				}
// // 			}
// // 			pthread_mutex_unlock(&coder->simu->state_lock);
// // 		}
			
// // 	}

	
	
	
// // 	return (NULL);
// // }

// int ft_read(pthread_mutex_t *mutex, int *is_on)
// {
//     int var;

//     pthread_mutex_lock(mutex);
//     var = *is_on;
//     pthread_mutex_unlock(mutex);
//     return var;
// }

// void *routine(void *args)
// {
//     t_coder *coder;
//     t_dongle *first_dongle;
//     t_dongle *second_dongle;

//     coder = (t_coder*)args;
    
//     // 1. ترتيب الوصلات لمنع الـ Deadlock
//     if (coder->right_dongle->id < coder->left_dongle->id)
//     {
//         first_dongle = coder->right_dongle;
//         second_dongle = coder->left_dongle;
//     }
//     else
//     {
//         first_dongle = coder->left_dongle;
//         second_dongle = coder->right_dongle;
//     }

//     if (coder->id % 2 == 0)
//         usleep(1000);

//     while (!ft_read(&coder->simu->state_lock, &coder->simu->is_simulation_over))
//     {
//         // فحص سريع وآمن لانتهاء المحاكاة (قفل ثم فتح فوراً)
//         pthread_mutex_lock(&coder->simu->state_lock);
//         if (coder->simu->is_simulation_over)
//         {
//             pthread_mutex_unlock(&coder->simu->state_lock);
//             return (NULL);
//         }
//         pthread_mutex_unlock(&coder->simu->state_lock);

//         // التحقق من عدد مرات التجميع المطلوبة
//         pthread_mutex_lock(&coder->coder_lock);
//         if (coder->compiles_count == coder->data->number_of_compiles_required)
//         {
//             pthread_mutex_unlock(&coder->coder_lock);
//             return (NULL);
//         }
//         pthread_mutex_unlock(&coder->coder_lock);
//         usleep(1000);
        
//         // 2. أخذ الوصلات معاً
//         if (take_dongle(coder, first_dongle, second_dongle))
//         {

//             pthread_mutex_lock(&coder->simu->state_lock);
//             if (coder->simu->is_simulation_over)
//             {
//                 pthread_mutex_unlock(&coder->simu->state_lock);
//                 return (NULL);
//             }
//             pthread_mutex_unlock(&coder->simu->state_lock);

//             // تحديث وقت آخر تجميع
//             if (coder->simu->is_simulation_over == 0)
//             {
//                 pthread_mutex_lock(&coder->coder_lock);
//                 coder->last_time_compilation = get_time_of_ms();
//                 pthread_mutex_unlock(&coder->coder_lock);
//             }

//             // طباعة Compiling
//             pthread_mutex_lock(&coder->simu->print_lock);
//             printf("%ld %d is compiling\n", get_time_of_ms() - coder->simu->start_time, coder->id);
//             pthread_mutex_unlock(&coder->simu->print_lock);

//             // النوم أثناء التجميع
//             if (ft_usleep(coder->simu, coder->data->time_to_compile))
//             {
//                 take_off_dongle(first_dongle, second_dongle);
//                 return (NULL);
//             }

//             // تحرير الوصلات فوراً بعد التجميع
//             take_off_dongle(first_dongle, second_dongle);

//             // زيادة عداد التجميع
//             pthread_mutex_lock(&coder->coder_lock);
//             coder->compiles_count++;
//             pthread_mutex_unlock(&coder->coder_lock);

//             // مرحلة التصحيح (Debugging)
//             pthread_mutex_lock(&coder->simu->print_lock);
//             printf("%ld %d is debugging\n", get_time_of_ms() - coder->simu->start_time, coder->id);
//             pthread_mutex_unlock(&coder->simu->print_lock);

//             if (ft_usleep(coder->simu, coder->data->time_to_debug))
//                 return (NULL);

//             // مرحلة إعادة الهيكلة (Refactoring)
//             pthread_mutex_lock(&coder->simu->print_lock);
//             printf("%ld %d is refactoring\n", get_time_of_ms() - coder->simu->start_time, coder->id);
//             pthread_mutex_unlock(&coder->simu->print_lock);

//             if (ft_usleep(coder->simu, coder->data->time_to_refactor))
//                 return (NULL);
//         }
//     }
//     return (NULL);
// }


// static int	create_coders(t_sumilation *sum)
// {
// 	int	i;

// 	i = 0;
// 	while (i < sum->data->number_of_coders)
// 	{
// 		pthread_create(&sum->coder[i].thread_id, NULL, routine, (void *)&sum->coder[i]);
// 		i++;
// 	}
// 	create_monitor(sum);
// 	i = 0;
// 	while (i < sum->data->number_of_coders)
// 	{
// 		pthread_join(sum->coder[i].thread_id, NULL);
// 		i++;
// 	}
// 	return (1);
// }

// void	sumilation(t_sumilation *sum)
// {

// 	init_mutex_dongle(sum);
// 	pthread_mutex_init(&sum->state_lock, NULL);
// 	pthread_mutex_init(&sum->print_lock, NULL);
// 	sum->start_time = get_time_of_ms();
// 	create_coders(sum);
// 	pthread_mutex_init(&sum->state_lock, NULL);
// 	pthread_join(sum->monitor_id, NULL);
// }
