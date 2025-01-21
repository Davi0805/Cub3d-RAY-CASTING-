/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:30:11 by davi              #+#    #+#             */
/*   Updated: 2025/01/21 17:35:42 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square(t_mlx_data mlx, int x, int y, int size, int color)
{
    int sx = x - size / 2;
    int sy = y - size / 2;
    int ex = sx + size;
    int ey = sy + size;

    for (int i = sx; i < ex; i++)
    {
        for (int j = sy; j < ey; j++)
        {
            put_pixel(mlx, i, j, color);
        }
    }
}

void draw_player(t_cub head)
{
    int x = head.player.px;
    int y = head.player.py;
    
    
    draw_square(head.mlx, x, y, 25, 0xFF0000);

    float line_len = SCALE * 2;
    float dx = cos(head.player.pa) * line_len;
    float dy = sin(head.player.pa) * line_len;
    

    
}

void drawMiniMap(t_cub head)
{
    int x;
    int y;

    x = 0;
    y = -1;
    while (head.map[++y])
    {
        x = -1;
        while(head.map[y][++x])
        {
            if (head.map[y][x] == '1')
                draw_square(head.mlx, x * (SCALE + 1), y * (SCALE + 1), SCALE, 0xFFFF00); // + 1 to create a 1 pixel gap
            else if (head.map[y][x] == '0' || head.map[y][x] == 'x')
                draw_square(head.mlx, x * (SCALE + 1), y * (SCALE + 1), SCALE, 0x808080);
        }      
    }
}

void drawRays()
{
    
}