#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>



typedef struct s_data {
	long number_of_coders;
	long time_to_burnout;
	long time_to_compile;
	long time_to_debug;
	long time_to_refactor;
	long number_of_compiles_required;
	long dongle_cooldown;
	int scheduler;
}	t_data;


typedef struct s_dongle {
	int	id;
	int is_free;
	long	last_released_time;
	pthread_mutex_t lock;
} t_dongle;

typedef struct	s_coder {
	int	id;
	pthread_t	thread_id;
	long	last_time_compilation;
	int	compiles_count;
	int	is_finished;
	t_dongle	*right_dongle;
	t_dongle	*left_dongle;
	t_data *data;
}	t_coder;

typedef struct s_sumilation {
	t_coder *coder;
	t_dongle *dongle;
	t_data *data;
} t_sumilation;




int ft_parsing(int ac, char **ar);
long ft_atoi(char *s);
t_data *intilize_data(char **ar);
t_sumilation *intit_sumlation(char **ar);
void	sumilation(t_sumilation *sum);



#endif