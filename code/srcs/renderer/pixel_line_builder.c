#include "cub3d.h"


// Converte estrutura com canais de cor separadas para um int
// TODO: Talvez modificar para suportar transparencia
int split_to_color(t_rgb color)
{
    int result;

    result = (color.r << 16) | (color.g << 8) | color.b;
    return result;
}

void DrawVertPixelLine(t_cub *head, int color, t_ray *ray, int x) //todo change whats recieved
{
    // Ceiling - pinta do inicio ate 1 pixel antes da parede
    DrawLine(head->mlx, x, 0, x, ray->drawStart - 1, split_to_color(head->assets.ceil_color));

    // Wall 
    DrawLine(head->mlx, x, ray->drawStart, x, ray->drawEnd, color);

    // Floor - pinta a partir de 1 pixel depois da parede ate o limite da janela
    DrawLine(head->mlx, x, ray->drawEnd + 1, x, HEIGHT - 1, split_to_color(head->assets.floor_color));
}