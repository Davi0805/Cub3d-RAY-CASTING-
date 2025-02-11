/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:17 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:46:47 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	return ;
}

// Calculate step and side dist
static void	get_side_dist(const t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * \
		ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * \
		ray->delta_dist_y;
	}
	return ;
}

// Perform DDA
static void	cast_ray(t_ray *ray, char **map, t_cub *head)
{
	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_y >= head->map_height
			|| ray->map_x >= head->map_l_lens[ray->map_y]
			|| map[ray->map_y][ray->map_x] == '1'
			|| map[ray->map_y][ray->map_x] == '\0'
			|| map[ray->map_y][ray->map_x] == '\n')
		{
			ray->hit = 1;
			return ;
		}
	}
}

// Calculate distance and height
static void	build_ray(t_player *player, t_ray *ray )
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + \
							(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + \
							(1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT;
	return ;
}

int	raycaster(t_cub *head)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&head->player, &ray, x);
		get_side_dist(&head->player, &ray);
		cast_ray(&ray, head->map, head);
		build_ray(&head->player, &ray);
		draw_vline_textured(head, &ray, x);
		x++;
	}
	return (0);
}
