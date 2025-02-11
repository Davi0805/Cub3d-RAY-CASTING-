/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:10:30 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:42:00 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Rotação de um Vetor em 2D
 * Para rotacionar um vetor (x, y) em um ângulo θ, usamos a matriz de rotação:
 * x′=xcos⁡(θ)−ysin⁡(θ)
 * y′=xsin⁡(θ)+ycos⁡(θ)
 * 
 * The dir plane and the camera plane have to be perpendicular so they both
 *  rotate the same
*/
// rotates player and camara right
void	player_rotate_right(t_cub *head, t_player *player)
{
	double	rot_speed;
	double	temp;

	rot_speed = ROTSPEED * head->delta_time;
	temp = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) \
					- player->dir_y * sin(rot_speed);
	player->dir_y = temp * sin(rot_speed) + player->dir_y * cos(rot_speed);
	temp = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) \
					- player->plane_y * sin(rot_speed);
	player->plane_y = temp * sin(rot_speed) + player->plane_y * cos(rot_speed);
}

// rotates player and camara right
void	player_rotate_left(t_cub *head, t_player *player)
{
	double	rot_speed;
	double	temp;

	rot_speed = -ROTSPEED * head->delta_time;
	temp = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) \
					- player->dir_y * sin(rot_speed);
	player->dir_y = temp * sin(rot_speed) + player->dir_y * cos(rot_speed);
	temp = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) \
					- player->plane_y * sin(rot_speed);
	player->plane_y = temp * sin(rot_speed) + player->plane_y * cos(rot_speed);
}
