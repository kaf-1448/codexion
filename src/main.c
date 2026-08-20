#include    "../library/codexion.h"

int main(int ac, char **ar)
{
    if (ft_parsing(ac, ar))
        return 1;

    // t_sumilation *sum = intit_sumlation(ar);
    // sumilation(sum);
    struct timeval tv;

    // Fetch current system time
    if (gettimeofday(&tv, NULL) == 0) {
        printf("Seconds since Epoch: %ld\n", (long)tv.tv_sec);

    } else {
        perror("gettimeofday failed");
        return 1;
    }

    
    return 0;
}