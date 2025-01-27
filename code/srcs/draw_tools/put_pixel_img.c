/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:27:47 by artuda-s          #+#    #+#             */
/*   Updated: 2025/01/27 17:27:53 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	PutPixelToImg(t_mlx_data mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = mlx.img_addr + (y * mlx.size_line + x * (mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
