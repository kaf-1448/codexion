#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>



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


typedef struct	s_coder {
	int id;
}	t_coder;




int ft_parsing(int ac, char **ar, t_data *args);


#endif