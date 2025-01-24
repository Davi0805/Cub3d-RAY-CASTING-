#include "cub3d.h"

static void InitRay(t_player *player, t_ray *ray, int x)
{
    // INIT
    ray->cameraX = 2 * x / (double)WIDTH - 1;
    ray->DirX = player->dirX + player->planeX * ray->cameraX;
    ray->DirY = player->dirY + player->planeY * ray->cameraX;
    ray->mapX = (int)player->posX;
    ray->mapY = (int)player->posY;
    ray->deltaDistX = fabs(1 / ray->DirX);
    ray->deltaDistY = fabs(1 / ray->DirY);
    ray->hit = 0;
    return ;
}

// Calculate step and side dist
static void GetSideDist(const t_player *player, t_ray *ray)
{
    // X axis 0->
    if (ray->DirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
    }
    // Y axis 0v
    if (ray->DirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - player->posY) * ray->deltaDistY;
    }
    return ;
}

// Perform DDA
static void CastRay(t_ray *ray, char **map)
{
    while (true)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }

        if (map[ray->mapY][ray->mapX] == '1' 
         || ray->mapX < 0 
         || ray->mapY < 0 
         || map[ray->mapY] == NULL 
         || map[ray->mapY][ray->mapX] == '\n'
         || map[ray->mapY][ray->mapX] == '\0')
        {
            ray->hit = 1;
            return ;
        }
    }
}

// Calculate distance and height
static void BuildRay(t_player *player, t_ray *ray )
{
    // get the Wall distance
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - player->posX + (1 - ray->stepX) / 2) / ray->DirX;
    else
        ray->perpWallDist = (ray->mapY - player->posY + (1 - ray->stepY) / 2) / ray->DirY;

    // choose a wall height
    ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);

    // start of the wall
    ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
    if (ray->drawStart < 0)
        ray->drawStart = 0;

    // end of the wall
    ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
    if (ray->drawEnd >= HEIGHT)
        ray->drawEnd = HEIGHT;
    return ;
}

int Raycaster(t_cub *head)
{
    t_ray ray;
    for (int x = 0; x < WIDTH; x++)
    {
        // start the current ray
        InitRay(&head->player, &ray, x);
        // get side distance and step based on direction
        GetSideDist(&head->player, &ray);
        // dda until hit a wall
        CastRay(&ray, head->map);
        // Start and end position of the wall hit
        BuildRay(&head->player, &ray);

        //todo side colors. CHANGE THIS
       int color = 0x0000FF;
        if (ray.side)
            color = 0xFF0000;

        // Drawing every vertical line of pixels of the image
        DrawVertPixelLine(head, color, &ray, x);
    }
    // put to the screen
    mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    return (0);
}
