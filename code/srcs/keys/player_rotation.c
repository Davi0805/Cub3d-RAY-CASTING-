/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:10:30 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:34:40 by artuda-s         ###   ########.fr       */
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

	rot_speed = ROTSPEED * head->deltaTime;
	temp = player->dirX;
	player->dirX = player->dirX * cos(rot_speed) \
					- player->dirY * sin(rot_speed);
	player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
	temp = player->planeX;
	player->planeX = player->planeX * cos(rot_speed) \
					- player->planeY * sin(rot_speed);
	player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}

// rotates player and camara right
void	player_rotate_left(t_cub *head, t_player *player)
{
	double	rot_speed;
	double	temp;

	rot_speed = -ROTSPEED * head->deltaTime;
	temp = player->dirX;
	player->dirX = player->dirX * cos(rot_speed) \
					- player->dirY * sin(rot_speed);
	player->dirY = temp * sin(rot_speed) + player->dirY * cos(rot_speed);
	temp = player->planeX;
	player->planeX = player->planeX * cos(rot_speed) \
					- player->planeY * sin(rot_speed);
	player->planeY = temp * sin(rot_speed) + player->planeY * cos(rot_speed);
}
