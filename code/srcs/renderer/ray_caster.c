/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:17 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 19:33:12 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->DirX = player->dirX + player->planeX * ray->cameraX;
	ray->DirY = player->dirY + player->planeY * ray->cameraX;
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	ray->deltaDistX = fabs(1 / ray->DirX);
	ray->deltaDistY = fabs(1 / ray->DirY);
	ray->hit = 0;
	return ;
}

// Calculate step and side dist
static void	get_side_dist(const t_player *player, t_ray *ray)
{
	if (ray->DirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
	}
	if (ray->DirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->posY) * ray->deltaDistY;
	}
	return ;
}

// Perform DDA
static void	cast_ray(t_ray *ray, char **map, t_cub *head)
{
	while (true)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapX < 0 || ray->mapY < 0
			|| ray->mapY >= head->mapHeight
			|| ray->mapX >= head->mapLineLens[ray->mapY]
			|| map[ray->mapY][ray->mapX] == '1'
			|| map[ray->mapY][ray->mapX] == '\0'
			|| map[ray->mapY][ray->mapX] == '\n')
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
		ray->perpWallDist = (ray->mapX - player->posX + \
							(1 - ray->stepX) / 2) / ray->DirX;
	else
		ray->perpWallDist = (ray->mapY - player->posY + \
							(1 - ray->stepY) / 2) / ray->DirY;
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT;
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
