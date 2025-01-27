/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:24:14 by artuda-s          #+#    #+#             */
/*   Updated: 2025/01/27 18:26:30 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This checks for keys that are pressed (flaged as true) and changes
// player dir and pos values
static void	UpdatePlayerPosition(t_cub *head)
{
	t_moves	*moves;

	moves = &head->player.moves;
	if (moves->w_key == true)
		PlayerForward(&head->player, head->map, head);
	if (moves->s_key == true)
		PlayerBackward(&head->player, head->map, head);
	if (moves->a_key == true)
		PlayerLeft(&head->player, head->map, head);
	if (moves->d_key == true)
		PlayerRight(&head->player, head->map, head);
	if (moves->r_key == true)
		PlayerRotateRight(head, &head->player);
	if (moves->l_key == true)
		PlayerRotateLeft(head, &head->player);
	return ;
}

// Game loop that will read player movements, cast 
// rays and draw the map accordingly to its location
int	UpdateLoop(t_cub *head)
{
	double	fps;

	head->deltaTime = DeltaTime(&head->time);
	gettimeofday(&head->time, NULL);
	UpdatePlayerPosition(head);
	Raycaster(head);
	mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, \
							head->mlx.img_ptr, 0, 0);
	mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
	head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, \
							HEIGHT);
	head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, \
							&head->mlx.bits_per_pixel, \
							&head->mlx.size_line, &head->mlx.endian);
	fps = 1 / head->deltaTime;
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, \
							WIDTH - 50, 15, 0xFFFFFF, "FPS: ");
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, \
							WIDTH - 25, 15, 0xFFFFFF, ft_itoa((int)fps));
	return (0);
}
