#include    "../library/codexion.h"

int is_valid_int(char *s)
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
	num = atoi(s);
    if (num > 2147483647)
		return 0;
    else if (num < 0)
		return 0;

    return 1;
}

int main(int ac, char **ar)
{
    // t_data data;

    if (ft_parsing(ac, ar))
        return 1;
    
}