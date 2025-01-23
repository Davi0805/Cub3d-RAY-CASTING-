#include "cub3d.h"

int Raycaster(t_cub *head)
{
    t_ray ray;
    for (int x = 0; x < WIDTH; x++)
    {
        // INIT
        ray.cameraX = 2 * x / (double)WIDTH - 1;
        ray.DirX = head->player.dirX + head->player.planeX * ray.cameraX;
        ray.DirY = head->player.dirY + head->player.planeY * ray.cameraX;
        ray.mapX = (int)head->player.posX;
        ray.mapY = (int)head->player.posY;
        ray.deltaDistX = fabs(1 / ray.DirX);
        ray.deltaDistY = fabs(1 / ray.DirY);
        ray.hit = 0;
        int color = 0x0000FF;

        // Calculate step and side dist
        if (ray.DirX < 0)
        {
            ray.stepX = -1;
            ray.sideDistX = (head->player.posX - ray.mapX) * ray.deltaDistX;
        }
        else
        {
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - head->player.posX) * ray.deltaDistX;
        }

        if (ray.DirY < 0)
        {
            ray.stepY = -1;
            ray.sideDistY = (head->player.posY - ray.mapY) * ray.deltaDistY;
        }
        else
        {
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - head->player.posY) * ray.deltaDistY;
        }


        // Perform DDA
        while (ray.hit == 0)
        {
            if (ray.sideDistX < ray.sideDistY)
            {
                ray.sideDistX += ray.deltaDistX;
                ray.mapX += ray.stepX;
                ray.side = 0;
            }
            else
            {
                ray.sideDistY += ray.deltaDistY;
                ray.mapY += ray.stepY;
                ray.side = 1;
            }

            //? probably not needed
            if (ray.mapX < 0 || ray.mapY < 0 || 
            ray.mapX >= ((int)ft_strlen(head->map[ray.mapY]) - 1) ||
            head->map[ray.mapY] == NULL)
            {
                ray.hit = 1;
                break ;
            }
            if (head->map[ray.mapY][ray.mapX] == '1')
                ray.hit = 1;
        }


        // Calculate distance and height
        if (ray.side == 0)
            ray.perpWallDist = (ray.mapX - head->player.posX + (1 - ray.stepX) / 2) / ray.DirX;
        else
            ray.perpWallDist = (ray.mapY - head->player.posY + (1 - ray.stepY) / 2) / ray.DirY;


        ray.lineHeight = (int)(HEIGHT / ray.perpWallDist);
        ray.drawStart = -ray.lineHeight / 2 + HEIGHT / 2;
        if (ray.drawStart < 0)
            ray.drawStart = 0;

        ray.drawEnd = ray.lineHeight / 2 + HEIGHT / 2;
        if (ray.drawEnd >= HEIGHT)
            ray.drawEnd = HEIGHT;
        
        
        if (ray.side)
            color = 0xFF0000;

        // printf("\nx %d\n:",x);
        
        // printf("stepX [%d]  stepY  [%d]\n", ray.stepX, ray.stepY);
        // printf("sideDistX   [%f]   sideDistY  [%f]\n", ray.sideDistX, ray.sideDistY);
        // printf("deltaDistX  [%f]   deltaDistY   [%f]\n", ray.deltaDistX, ray.deltaDistY);
        // printf("mapX [%d]  mapY [%d]\n", ray.mapX, ray.mapY);
        // printf("perpWallDist  [%f]   lineHeight  [%d]\n", ray.perpWallDist , ray.lineHeight);
        // printf("start %d end %d\n", ray.drawStart, ray.drawEnd);
        // Draw line
        DrawLine(head->mlx, x, ray.drawStart, x, ray.drawEnd, color);
    }

    mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    return (0);
}