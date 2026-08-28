#include    "../library/codexion.h"

int main(int ac, char **ar)
{
    if (ft_parsing(ac, ar))
        return 1;

    t_sumilation *sum = intit_sumlation(ar);
    sumilation(sum);
    // int i;

    // i = 0;
    // while(i < sum->data->number_of_coders)
    // {
    //     printf("coder id %d\n", sum->coder[i].id);
    //     printf("dongle left %d\n", sum->coder[i].left_dongle->id);
    //     printf("dongle right id %d\n", sum->coder[i].right_dongle->id);
    //     printf("is availble %d\n", sum->coder[i].left_dongle->is_free);
    //     i++;
    // }


    
    return 0;
}