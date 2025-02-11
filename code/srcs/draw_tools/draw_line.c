/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:57 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:27:22 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA line draw algorithm
// Draws a line starting at (x1,y1) and ending at (x2,y2) with color <color>
// void	draw_line(t_mlx_data mlx, int x1, int y1, int x2, int y2, int color)
void	draw_line(t_mlx_data mlx, t_point p1, t_point p2, int color)
{
	t_dda	dda;
	int		i;

	dda.dx = p2.x - p1.x;
	dda.dy = p2.y - p1.y;
	if (abs(dda.dx) > abs(dda.dy))
		dda.steps = abs(dda.dx);
	else
		dda.steps = abs(dda.dy);
	dda.xinc = dda.dx / (float)dda.steps;
	dda.yinc = dda.dy / (float)dda.steps;
	dda.x = p1.x;
	dda.y = p1.y;
	i = 0;
	while (i <= dda.steps)
	{
		put_pixel_to_img(mlx, (int)(dda.x + 0.5), (int)(dda.y + 0.5), color);
		dda.x += dda.xinc;
		dda.y += dda.yinc;
		i++;
	}
}
