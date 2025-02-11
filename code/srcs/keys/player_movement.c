/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:38:58 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:39:15 by artuda-s         ###   ########.fr       */
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
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX += player->dirX * MOVESPEED * head->delta_time;
	p_mapx = (int)(player->posX);
	p_mapy = (int)(player->posY + player->dirY * MOVESPEED * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
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
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX -= player->dirX * MOVESPEED * head->delta_time;
	p_mapy = (int)(player->posY - player->dirY * MOVESPEED * head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
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
	p_mapx = (int)(player->posX - player->plane_x * MOVESPEED * \
			head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX -= player->plane_x * MOVESPEED * head->delta_time;
	p_mapy = (int)(player->posY - player->plane_y * MOVESPEED * \
			head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY -= player->plane_y * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// + head->delta_time * pDir
void	player_right(t_player *player, char **map, t_cub *head)
{
	int	p_mapy;
	int	p_mapx;

	p_mapy = (int)(player->posY);
	p_mapx = (int)(player->posX + player->plane_x * head->delta_time);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posX += player->plane_x * head->delta_time;
	p_mapy = (int)(player->posY + player->plane_y * head->delta_time);
	p_mapx = (int)(player->posX);
	if (p_mapx > 0 && p_mapy > 0
		&& p_mapy < head->map_height && p_mapx < head->map_l_lens[p_mapy]
		&& map[p_mapy][(int)(p_mapx)] != '1')
		player->posY += player->plane_y * head->delta_time;
}
