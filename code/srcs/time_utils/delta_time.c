#include "cub3d.h"

double DeltaTime(struct timeval *old)
{
    struct timeval new;
    
    gettimeofday(&new, NULL);

    double deltaTime = (new.tv_sec - old->tv_sec) + (new.tv_usec - old->tv_usec) * 1e-6;
    return (deltaTime <= 0 ? 1/120 : deltaTime);
}
