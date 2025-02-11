/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:38:58 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:45:49 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// If possible, updates player x and y position on the map by 
// + head->delta_time * pDir
void	player_forward(t_player *player, char **map, t_cub *head)
{
	int	p_map_y;
	int	p_map_x;

	p_map_y = (int)(player->pos_y);
	p_map_x = (int)(player->pos_x + player->dir_x * MOVESPEED \
			* head->delta_time);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_x += player->dir_x * MOVESPEED * head->delta_time;
	p_map_x = (int)(player->pos_x);
	p_map_y = (int)(player->pos_y + player->dir_y * MOVESPEED \
			* head->delta_time);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_y += player->dir_y * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// - head->delta_time * pDir
void	player_backward(t_player *player, char **map, t_cub *head)
{
	int	p_map_y;
	int	p_map_x;

	p_map_y = (int)(player->pos_y);
	p_map_x = (int)(player->pos_x - player->dir_x * MOVESPEED \
			* head->delta_time);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_x -= player->dir_x * MOVESPEED * head->delta_time;
	p_map_y = (int)(player->pos_y - player->dir_y * MOVESPEED \
			* head->delta_time);
	p_map_x = (int)(player->pos_x);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_y -= player->dir_y * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// - head->delta_time * pDir
void	player_left(t_player *player, char **map, t_cub *head)
{
	int	p_map_y;
	int	p_map_x;

	p_map_y = (int)(player->pos_y);
	p_map_x = (int)(player->pos_x - player->plane_x * MOVESPEED * \
			head->delta_time);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_x -= player->plane_x * MOVESPEED * head->delta_time;
	p_map_y = (int)(player->pos_y - player->plane_y * MOVESPEED * \
			head->delta_time);
	p_map_x = (int)(player->pos_x);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_y -= player->plane_y * MOVESPEED * head->delta_time;
}

// If possible, updates player x and y position on the map by 
// + head->delta_time * pDir
void	player_right(t_player *player, char **map, t_cub *head)
{
	int	p_map_y;
	int	p_map_x;

	p_map_y = (int)(player->pos_y);
	p_map_x = (int)(player->pos_x + player->plane_x * head->delta_time);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_x += player->plane_x * head->delta_time;
	p_map_y = (int)(player->pos_y + player->plane_y * head->delta_time);
	p_map_x = (int)(player->pos_x);
	if (p_map_x > 0 && p_map_y > 0
		&& p_map_y < head->map_height && p_map_x < head->map_l_lens[p_map_y]
		&& map[p_map_y][(int)(p_map_x)] != '1')
		player->pos_y += player->plane_y * head->delta_time;
}
