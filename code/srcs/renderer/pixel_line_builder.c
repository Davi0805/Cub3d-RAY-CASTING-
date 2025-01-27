/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_line_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:13:43 by artuda-s          #+#    #+#             */
/*   Updated: 2025/01/27 18:15:02 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Converte estrutura com canais de cor separadas para um int
// TODO: Talvez modificar para suportar transparencia
int	split_to_color(t_rgb color)
{
	int	result;

	result = (color.r << 16) | (color.g << 8) | color.b;
	return (result);
}

void	DrawVertPixelLine(t_cub *head, int color, t_ray *ray, int x)
{
	DrawLine(head->mlx, x, 0, x, ray->drawStart - 1, \
			split_to_color(head->assets.ceil_color));
	DrawLine(head->mlx, x, ray->drawStart, x, ray->drawEnd, color);
	DrawLine(head->mlx, x, ray->drawEnd + 1, x, HEIGHT - 1, \
			split_to_color(head->assets.floor_color));
}
