#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_sumilation t_sumilation;
typedef struct s_queue t_queue;

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
	pthread_cond_t cond;
	t_queue *queue;
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

typedef struct s_queue {
	t_coder *coders[2];
} t_queue;

struct s_sumilation {
	pthread_t monitor_id;
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
// int	take_dongle(t_coder *coder);
int take_dongle(t_coder *coder, t_dongle *dongle);
void take_off_dongle(t_dongle *dongle);
// void take_off_dongle(t_coder *coder, t_dongle *dongle);

// monitor
void create_monitor(t_sumilation *simu);


// scheduler
void	organize_queue(t_dongle *dongle, t_coder *coder);
void	remove_from_queue(t_dongle *dongle, t_coder *coder);

#endif