/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:30:32 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:39:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_start_dir_2(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->plane_x = 0;
		player->plane_y = FOV;
	}
	else if (direction == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->plane_x = 0;
		player->plane_y = -FOV;
	}
}

void	get_start_dir(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->plane_x = FOV;
		player->plane_y = 0;
	}
	else if (direction == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->plane_x = -FOV;
		player->plane_y = 0;
	}
	else
		get_start_dir_2(player, direction);
}

bool	flood_fill(char **map, int y, int x, char to_fill)
{
	bool	edge;

	if (x < 0 || y < 0 || map[y] == NULL \
		|| (map[y][x] == '\n' || map[y][x] == '\0'))
		return (true);
	if (map[y][x] != to_fill && !ft_strchr("NSEW", map[y][x]))
		return (false);
	map[y][x] = 'x';
	edge = false;
	edge |= flood_fill(map, y, x - 1, to_fill);
	edge |= flood_fill(map, y, x + 1, to_fill);
	edge |= flood_fill(map, y - 1, x, to_fill);
	edge |= flood_fill(map, y + 1, x, to_fill);
	return (edge);
}

static bool	map_not_closed(t_cub *head)
{
	return (flood_fill(head->map, head->player.posY, \
			head->player.posX, '0'));
}

uint8_t	verify_map(t_cub *head)
{
	if (has_bad_chars(head))
		return (MWRONG_FORMAT);
	if (map_not_closed(head))
		return (MWRONG_FORMAT);
	return (PARSE_SUCCESS);
}
