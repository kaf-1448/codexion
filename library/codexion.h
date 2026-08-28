#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_sumilation t_sumilation;

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
	long	last_time_compilation;
	int	compiles_count;
	int	is_finished;
	pthread_t	thread_id;
	pthread_mutex_t	coder_lock;
	t_dongle	*right_dongle;
	t_dongle	*left_dongle;
	t_data *data;
	t_sumilation *simu;
}	t_coder;

struct s_sumilation {
	long	start_time;
	int is_simulation_over;
	pthread_mutex_t print_lock;
	pthread_mutex_t state_lock;
	t_coder *coder;
	t_dongle *dongle;
	t_data *data;
};



// parsing
int ft_parsing(int ac, char **ar);
long ft_atoi(char *s);

// simulation
t_data *intilize_data(char **ar);
t_sumilation *intit_sumlation(char **ar);
void	sumilation(t_sumilation *sum);
void	init_mutex_dongle(t_sumilation *sum);
long	get_time_of_ms(void);
int	ft_usleep(t_sumilation *sim, long target);

// dongles
int	take_dongle(t_coder *coder);
void take_off_dongle(t_dongle *first, t_dongle *second);

// monitor
void create_monitor(t_sumilation *simu);

#endif