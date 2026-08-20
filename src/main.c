#include    "../library/codexion.h"

int main(int ac, char **ar)
{
    if (ft_parsing(ac, ar))
        return 1;
    t_data *data =  intilize_data(ar);
    printf("%ld\n", data->number_of_coders);
    printf("%d\n", data->scheduler);
    return 0;
}