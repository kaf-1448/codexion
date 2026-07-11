#include "../library/codexion.h"

static long ft_atoi(char *s)
{
	int	i;
	long	res;
	int sign;

	sign = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 9))
		i++;

	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}

	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] -'0');
		i++;
	}
	return (res * sign);
}


static int is_valid_int(char *s)
{
    long    num;
    int    i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return 0;
		i++;
	}
	num = ft_atoi(s);
    if (num > 2147483647)
		return 0;
    else if (num < 0)
		return 0;

    return 1;
}


int ft_parsing(int ac, char **ar)
{
    if (ac < 9)
		return (write(1, "Argument is fails", 18));
	if (!is_valid_int(ar[1]))
    	return (write(1, "The number of coder is incorrect\n", 34));
	if (!is_valid_int(ar[2]))
    	return (write(1, "The time_to_burnou is incorrect\n", 33));
	if (!is_valid_int(ar[3]))
    	return (write(1, "The time_to_compile is incorrect\n", 34));
	if (!is_valid_int(ar[4]))
    	return (write(1, "The time_to_debug is incorrect\n", 32));
	if (!is_valid_int(ar[5]))
    	return (write(1, "The time_to_refactor is incorrect\n", 35));
	if (!is_valid_int(ar[6]))
    	return (write(1, "The number_of_compiles_required is incorrect\n", 46));
	if (!is_valid_int(ar[7]))
    	return (write(1, "The dongle_cooldown is incorrect\n", 34));
    if (strcmp("fifo", ar[8]) != 0 && strcmp("edf", ar[8]) != 0)
		return (write(1, "The scheduler is incorrect must be 'fifo' or 'edf'\n", 52));
    return 0;
}
