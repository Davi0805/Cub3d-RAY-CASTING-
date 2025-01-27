#include "cub3d.h"

void DrawVertPixelLine(t_cub *head, int color, t_ray *ray, int x) //todo change whats recieved
{
    // Ceiling
    DrawLine(head->mlx, x, 0, x, ray->drawStart - 1, 0x00FFFF);

    // Wall 
    DrawLine(head->mlx, x, ray->drawStart, x, ray->drawEnd, color);

    // Floor
    DrawLine(head->mlx, x, ray->drawEnd + 1, x, HEIGHT - 1, 0xFFA500);
}