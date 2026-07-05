#include "../library/codexion.h"

int ft_parsing(int ac, char **ar, t_data *args)
{
    int false_args;

    false_args = 0;
    if (ac < 9)
    {   
        false_args = 1;
        return false_args;
    }
    args->number_of_coders = atoi(ar[1]);
    args->time_to_burnout = atoi(ar[2]);
    args->time_to_compile = atoi(ar[3]);
    args->time_to_debug = atoi(ar[4]);
    args->time_to_refactor = atoi(ar[5]);
    args->number_of_compiles_required = atoi(ar[6]);
    args->dongle_cooldown = atoi(ar[7]);
    if (strcmp("fifo", ar[8]) == 0)
        args->scheduler = 1;
    else if (strcmp("edf", ar[8]) == 0)
        args->scheduler = 0;
    else 
        return false_args = 1;
    return false_args;
}
