/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:45:11 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:46:43 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This checks for keys that are pressed (flaged as true) and changes
// player dir and pos values
static void	update_player_pos(t_cub *head)
{
	t_moves	*moves;

	moves = &head->player.moves;
	if (moves->w_key == true)
		player_forward(&head->player, head->map, head);
	if (moves->s_key == true)
		player_backward(&head->player, head->map, head);
	if (moves->a_key == true)
		player_left(&head->player, head->map, head);
	if (moves->d_key == true)
		player_right(&head->player, head->map, head);
	if (moves->r_key == true)
		player_rotate_right(head, &head->player);
	if (moves->l_key == true)
		player_rotate_left(head, &head->player);
	return ;
}

// Game loop that will read player movements, cast 
// rays and draw the map accordingly to its location
int	update_loop(t_cub *head)
{
	double	fps;
	char	*fps_str;

	head->delta_time = delta_time(&head->time);
	gettimeofday(&head->time, NULL);
	update_player_pos(head);
	Raycaster(head);
	mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, \
			head->mlx.img_ptr, 0, 0);
	mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
	head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
	head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, \
			&head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
	fps = 1 / head->delta_time;
	fps_str = ft_itoa((int)fps);
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, WIDTH - 50, 15, \
			0xFFFFFF, "FPS: ");
	mlx_string_put(head->mlx.mlx_ptr, head->mlx.win_ptr, WIDTH - 25, 15, \
			0xFFFFFF, fps_str);
	free(fps_str);
	return (0);
}
