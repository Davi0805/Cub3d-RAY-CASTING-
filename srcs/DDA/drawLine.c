/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawLine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:38:40 by davi              #+#    #+#             */
/*   Updated: 2025/01/17 14:32:04 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx_data mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = mlx.img_addr + (y * mlx.size_line + x * (mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void    drawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2)
{
    t_dda dda;
    int i;

    dda.dx = x2 - x1;
    dda.dy = y2 - y1;
    
    if (abs(dda.dx) > abs(dda.dy))
        dda.steps = abs(dda.dx);
    else
        dda.steps = abs(dda.dy);
        
    dda.xinc = dda.dx / dda.steps;
    dda.yinc = dda.dy / dda.steps;

    i = 0;
    while (i <= dda.steps)
    {
        // ! SUBSTITUIR POR UMA LOGICA DE TEXTURA OU COR
        put_pixel(mlx, x1, y1, 0x0000FF);
        x1 += dda.xinc;
        y1 += dda.yinc;
        i++;
    } 
}