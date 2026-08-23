#include    "../library/codexion.h"

int main(int ac, char **ar)
{
    if (ft_parsing(ac, ar))
        return 1;

    t_sumilation *sum = intit_sumlation(ar);
    sumilation(sum);


    
    return 0;
}