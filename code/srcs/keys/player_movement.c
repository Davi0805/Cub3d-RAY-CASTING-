/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:38:58 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:38:23 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// If possible, updates player x and y position on the map by 
// + head->delta_time * pDir
void	player_forward(t_player *player, char **map, t_cub *head)
{
	int	p_mapy;
	int	p_mapx;

	p_mapy = (int)(player->posY);
	p_mapx = (int)(player->posX + player->dirX * MOVESPEED * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX += player->dirX * MOVESPEED * head->delta_time;
	p_mapx = (int)(player->posX);
	p_mapy = (int)(player->posY + player->dirY * MOVESPEED * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY += player->dirY * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// - head->delta_time * pDir
void	player_backward(t_player *player, char **map, t_cub *head)
{
	int	p_mapy;
	int	p_mapx;

	p_mapy = (int)(player->posY);
	p_mapx = (int)(player->posX - player->dirX * MOVESPEED * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX -= player->dirX * MOVESPEED * head->delta_time;
	p_mapy = (int)(player->posY - player->dirY * MOVESPEED * head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY -= player->dirY * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// - head->delta_time * pDir
void	player_left(t_player *player, char **map, t_cub *head)
{
	int	p_mapy;
	int	p_mapx;

	p_mapy = (int)(player->posY);
	p_mapx = (int)(player->posX - player->planeX * MOVESPEED * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX -= player->planeX * MOVESPEED * head->delta_time;
	p_mapy = (int)(player->posY - player->planeY * MOVESPEED * head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY -= player->planeY * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// + head->delta_time * pDir
void	player_right(t_player *player, char **map, t_cub *head)
{
	int	p_mapy;
	int	p_mapx;

	p_mapy = (int)(player->posY);
	p_mapx = (int)(player->posX + player->planeX * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX += player->planeX * head->delta_time;
	p_mapy = (int)(player->posY + player->planeY * head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->mapHeight && p_mapx < head->mapLineLens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY += player->planeY * head->delta_time;
}
