/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:10:46 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:31:25 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This sets a key flag to true when is pressed
int	KeyPressed(int key, t_cub *head)
{
	if (key == XK_Right)
		head->player.moves.r_key = true;
	else if (key == XK_Left)
		head->player.moves.l_key = true;
	else if (key == XK_w)
		head->player.moves.w_key = true;
	else if (key == XK_s)
		head->player.moves.s_key = true;
	else if (key == XK_a)
		head->player.moves.a_key = true;
	else if (key == XK_d)
		head->player.moves.d_key = true;
	else if (key == XK_Escape)
		exit_fun(head);
	return (0);
}

// This sets the key flag to false when released
int	KeyReleased(int key, t_cub *head)
{
	if (key == XK_Right)
		head->player.moves.r_key = false;
	if (key == XK_Left)
		head->player.moves.l_key = false;
	if (key == XK_w)
		head->player.moves.w_key = false;
	if (key == XK_s)
		head->player.moves.s_key = false;
	if (key == XK_a)
		head->player.moves.a_key = false;
	if (key == XK_d)
		head->player.moves.d_key = false;
	return (0);
}
