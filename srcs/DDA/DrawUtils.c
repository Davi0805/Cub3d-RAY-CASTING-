/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:30:11 by davi              #+#    #+#             */
/*   Updated: 2025/01/17 15:39:03 by davi             ###   ########.fr       */
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

    draw_square(head.mlx, x, y, SCALE, 0xFF0000);

    float line_len = SCALE * 2;
    float dx = cos(head.player.pa) * line_len;
    float dy = sin(head.player.pa) * line_len;
    
    drawLine(head.mlx, x, y, x + dx, y + dy);
    
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
                draw_square(head.mlx, x * SCALE, y * SCALE, SCALE, 0xFFFF00);
            else if (head.map[y][x] == '0')
                draw_square(head.mlx, x * SCALE, y * SCALE, SCALE, 0x808080);
        }      
    }
}

void drawRays()
{
    
}