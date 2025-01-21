/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawLine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:38:40 by davi              #+#    #+#             */
/*   Updated: 2025/01/21 17:31:38 by artuda-s         ###   ########.fr       */
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


void drawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2)
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
        put_pixel(mlx, (int)(dda.x + 0.5), (int)(dda.y + 0.5), 0x0000FF);

        // Atualiza as coordenadas com os incrementos
        dda.x += dda.xinc;
        dda.y += dda.yinc;

        i++;
    }
}
