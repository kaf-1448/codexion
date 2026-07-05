#include    "../library/codexion.h"

int main(int ac, char **ar)
{
    t_data data;

    if (ft_parsing(ac, ar, &data))
        return 1;
    printf("%ld\n", data.number_of_coders);
    printf("%d\n", data.scheduler);
}