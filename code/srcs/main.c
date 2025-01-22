/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/01/22 18:16:28 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
    if (ac != 2)
        return (PARSE_ERROR);
    
    // File type
    if (filetype_checker(av[1])) parseFailed (head, FTYPE_ERROR);
    // File opens
    if (isFileValid(av[1])) parseFailed (head, FINVALID_ERROR);
    // Has contents
    if (isFileEmpty(av[1])) parseFailed (head, FEMPTY_ERROR);
    
    // Heap storing the file contents into a buffer
    if (allocate_file(av, head)) parseFailed (head, PARSE_ERROR);
    // TEXTURES Validation
    if (textureValidator(head)) parseFailed(head, MWRONG_TEXTURE);

    // Read file contents and allocate map
    if (allocateMap(head, head->fcontent, av[1])) parseFailed(head, MWRONG_TEXTURE);
    // MAP Validation
    if (verifyMap(head)) parseFailed (head, MWRONG_TEXTURE);
    
    return (PARSE_SUCCESS);
}
    
uint8_t     setup_minilibx(t_cub *head)
{
    head->mlx.mlx_ptr = mlx_init();
    if (head->mlx.mlx_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.win_ptr = mlx_new_window(head->mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D - Oq tu quer ta mole");
    if (head->mlx.win_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    if (head->mlx.img_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    if (head->mlx.img_addr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);

    return (0);
}

void	ft_put_pixel(t_mlx_data mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = mlx.img_addr + (y * mlx.size_line + x * (mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}


void drawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2, int color)
{
    t_dda dda;
    int i;

    dda.dx = x2 - x1;
    dda.dy = y2 - y1;

    // Determina o número de passos necessários (baseado na maior diferença)
    if (abs(dda.dx) > abs(dda.dy))
        dda.steps = abs(dda.dx);
    else
        dda.steps = abs(dda.dy);

    // Calcula os incrementos para cada eixo
    dda.xinc = dda.dx / (float)dda.steps;
    dda.yinc = dda.dy / (float)dda.steps;

    // Inicializa as coordenadas com floats
    dda.x = x1;
    dda.y = y1;

    // Itera pelos passos para desenhar a linha
    i = 0;
    while (i <= dda.steps)
    {
        // Coloca o pixel arredondando as coordenadas
        ft_put_pixel(mlx, (int)(dda.x + 0.5), (int)(dda.y + 0.5), color);

        // Atualiza as coordenadas com os incrementos
        dda.x += dda.xinc;
        dda.y += dda.yinc;

        i++;
    }
}


int raycaster(t_cub *head)
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
        drawLine(head->mlx, x, ray.drawStart, x, ray.drawEnd, color);
    }

    mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    return (0);
}



int read_keys(int key, t_cub *head)
{
    if (key == XK_Escape)
        ExitFun(head);
    else if(key == XK_w) 
    {
        printf("pressed W\n");
        int y = (int)(head->player.posY);
        int x = (int)(head->player.posX + head->player.dirX * MOVESPEED);
        if (head->map[y][x] != '1')
            head->player.posX += head->player.dirX * MOVESPEED;
        
        x = (int)(head->player.posX);
        y = (int)(head->player.posY + head->player.dirY * MOVESPEED);
        if (head->map[y][x] != '1')
            head->player.posY += head->player.dirY * MOVESPEED;
    }
    else if(key == XK_s) 
    {
        printf("pressed S\n");
        int y = (int)(head->player.posY);
        int x = (int)(head->player.posX - head->player.dirX * MOVESPEED);
        if (head->map[y][x] != '1')
            head->player.posX -= head->player.dirX * MOVESPEED;
        y = (int)(head->player.posY - head->player.dirY * MOVESPEED);
        x = (int)(head->player.posX);
        if (head->map[y][x] != '1')
            head->player.posY -= head->player.dirY * MOVESPEED;
    }
    else if(key == XK_a)
    {
        printf("pressed A\n");
        int y = (int)(head->player.posY);
        int x = (int)(head->player.posX - head->player.planeX * MOVESPEED);
        if (head->map[y][x] != '1')
            head->player.posX -= head->player.planeX * MOVESPEED;
        y =(int)(head->player.posY - head->player.planeY * MOVESPEED);
        x = (int)(head->player.posX);
        if (head->map[y][x] != '1')
            head->player.posY -= head->player.planeY * MOVESPEED;
    }
    else if(key == XK_d)
    {
        printf("pressed D\n");
        int y = (int)(head->player.posY);
        int x =(int)(head->player.posX + head->player.planeX * MOVESPEED);
        if (head->map[y][x] != '1')
            head->player.posX += head->player.planeX * MOVESPEED;
        x = (int)(head->player.posY + head->player.planeY * MOVESPEED);
        y = (int)(head->player.posX);
        if (head->map[y][x] != '1')
            head->player.posY += head->player.planeY * MOVESPEED;
    }
    else if (key == XK_Left)
    {
        printf("pressed ->\n");
        double rot_speed;
        double old_dir_x;
        double old_plane_x;

        rot_speed = 0.1;
        old_dir_x = head->player.dirX;
        head->player.dirX = head->player.dirX * cos(rot_speed) - head->player.dirY * sin(rot_speed);
        head->player.dirY = old_dir_x * sin(rot_speed) + head->player.dirY * cos(rot_speed);
        old_plane_x = head->player.planeX;
        head->player.planeX = head->player.planeX * cos(rot_speed) - head->player.planeY * sin(rot_speed);
        head->player.planeY = old_plane_x * sin(rot_speed) + head->player.planeY * cos(rot_speed);
    }
    else if(key == XK_Right)
    {
        printf("pressed <-\n");
        double rot_speed;
        double old_dir_x;
        double old_plane_x;

        rot_speed = -0.1;
        old_dir_x = head->player.dirX;
        head->player.dirX = head->player.dirX * cos(rot_speed) - head->player.dirY * sin(rot_speed);
        head->player.dirY = old_dir_x * sin(rot_speed) + head->player.dirY * cos(rot_speed);
        old_plane_x = head->player.planeX;
        head->player.planeX = head->player.planeX * cos(rot_speed) - head->player.planeY * sin(rot_speed);
        head->player.planeY = old_plane_x * sin(rot_speed) + head->player.planeY * cos(rot_speed);
    }

    
    raycaster(head);
    
    return (0);
}

int main(int ac, char **av)
{
    t_cub head;

    // Init everything to 0's
    ft_bzero(&head, sizeof(head));
    // Valid file
    if (setup_validation(ac, av, &head))
        return (1);

    if (setup_minilibx(&head))
        return (1);
    
    // Actual program
    // posX and Y are given
    //! dirX and Y must be fetched based on its positioning on hasBadChars
    head.player.dirX = -1;
    head.player.dirY = 0;
    // This should be new variables out of player
    head.player.planeX = 0;
    head.player.planeY = 0.66;

    raycaster(&head);
    

     
//  mlx_loop_hook(head.mlx.mlx_ptr, raycaster, (void *)&head);
    mlx_key_hook(head.mlx.win_ptr, read_keys, &head);
	mlx_hook(head.mlx.win_ptr, DestroyNotify, 1L << 0, ExitFun, &head);
	mlx_loop(head.mlx.mlx_ptr);

    // Resource deallocation
    ExitFun(&head);
    return (0);
}