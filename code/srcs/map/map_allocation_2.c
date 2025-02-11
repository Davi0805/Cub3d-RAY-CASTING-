/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:01:00 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:04:25 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static bool	validate_remaining_lines(int fd)
{
	char	*line;
	bool	is_valid;

	is_valid = true;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_stremptyspaces(line))
			is_valid = false;
		free(line);
		line = get_next_line(fd);
	}
	return (is_valid);
}

static int	count_map_lines(int fd, char *first_line)
{
	char	*line;
	int		height;

	height = 0;
	line = first_line;
	while (line)
	{
		if (ft_stremptyspaces(line))
		{
			free(line);
			if (validate_remaining_lines(fd))
				return (height);
			else
				return (-1);
		}
		free(line);
		line = get_next_line(fd);
		height++;
	}
	return (height);
}

static char	*find_first_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		clear_remaining_lines(fd);
		return (NULL);
	}
	return (line);
}

int	get_map_height(char *map_path)
{
	int		fd;
	char	*first_line;
	int		height;

	fd = open(map_path, O_RDONLY);
	if (!fd)
		return (-1);
	first_line = find_first_map_line(fd);
	if (!first_line)
	{
		close(fd);
		return (-1);
	}
	height = count_map_lines(fd, first_line);
	close(fd);
	return (height);
}
