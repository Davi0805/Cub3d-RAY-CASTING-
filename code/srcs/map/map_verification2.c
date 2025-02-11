/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verification2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:29:28 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:35:06 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_char(char c)
{
	return (ft_strchr("01 ", c) != NULL);
}

static bool	setup_player(t_cub *head, char dir, int x, int y)
{
	get_start_dir(&head->player, dir);
	head->player.posX = x + 0.5f;
	head->player.posY = y + 0.5f;
	return (true);
}

static bool	check_line(t_cub *head, char *line, int y, bool *has_player)
{
	int	x;

	x = 0;
	while (line[x] != '\n' && line[x] != '\0')
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (*has_player)
				return (false);
			*has_player = setup_player(head, line[x], x, y);
		}
		else if (!is_valid_char(line[x]))
			return (false);
		x++;
	}
	return (true);
}

bool	has_bad_chars(t_cub *head)
{
	bool	has_player;
	int		y;

	has_player = false;
	y = 0;
	while (head->map[y])
	{
		if (!check_line(head, head->map[y], y, &has_player))
			return (true);
		y++;
	}
	return (!has_player);
}
