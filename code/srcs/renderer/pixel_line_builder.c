#include "cub3d.h"

void DrawVertPixelLine(t_cub *head, int color, t_ray *ray, int x) //todo change whats recieved
{
    // Wall 
    DrawLine(head->mlx, x, ray->drawStart, x, ray->drawEnd, color);
}