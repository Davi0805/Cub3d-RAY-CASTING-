/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_line_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:13:43 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:46:27 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Converte estrutura com canais de cor separadas para um int
int	split_to_color(t_rgb color)
{
	int	result;

	result = (color.r << 16) | (color.g << 8) | color.b;
	return (result);
}

static void	set_texture_data(t_davitone *n, void *texture, \
								int width, int height)
{
	n->texture = texture;
	n->tex_width = width;
	n->tex_height = height;
}

static void	init_wall_data(t_ray *ray, t_davitone *n, t_cub *head)
{
	if (ray->side == 0 && ray->dir_x > 0)
		set_texture_data(n, head->assets.ea, head->assets.ea_width, \
			head->assets.ea_height);
	else if (ray->side == 0)
		set_texture_data(n, head->assets.we, head->assets.we_width, \
			head->assets.we_height);
	else if (ray->dir_y > 0)
		set_texture_data(n, head->assets.so, head->assets.so_width, \
			head->assets.so_height);
	else
		set_texture_data(n, head->assets.no, head->assets.no_width, \
			head->assets.no_height);
	if (ray->side == 0)
		n->wall_x = head->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		n->wall_x = head->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	n->wall_x -= floor(n->wall_x);
	n->tex_x = (int)(n->wall_x * (double)n->tex_width);
	if (n->tex_x < 0)
		n->tex_x = 0;
	else if (n->tex_x >= n->tex_width)
		n->tex_x = n->tex_width - 1;
}

void	draw_vline_textured(t_cub *head, t_ray *ray, int x)
{
	t_davitone	n;
	int			y;

	init_wall_data(ray, &n, head);
	draw_line(head->mlx, (t_point){.x = x, .y = 0}, \
		(t_point){.x = x, .y = ray->draw_start - 1},
		split_to_color(head->assets.ceil_color));
	n.texture_data = (int *)mlx_get_data_addr(n.texture, \
											&head->mlx.bits_per_pixel, \
											&n.size_line, \
											&head->mlx.endian);
	n.step = 1.0 * (n.tex_height - 1) / ray->line_height;
	n.tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * n.step;
	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		n.tex_y = (int)n.tex_pos & (n.tex_height - 1);
		n.tex_pos += n.step;
		n.color = n.texture_data[n.tex_y * n.tex_width + n.tex_x];
		if (ray->side == 1)
			n.color = (n.color >> 1) & 8355711;
		put_pixel_to_img(head->mlx, x, y, n.color);
	}
	draw_line(head->mlx, (t_point){.x = x, .y = ray->draw_end + 1}, (t_point){\
	.x = x, .y = HEIGHT - 1}, split_to_color(head->assets.floor_color));
}
