/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:38:24 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:38:44 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_line(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO", 2) != 0 && ft_strncmp(line, "SO", 2) != 0 \
	&& ft_strncmp(line, "WE", 2) != 0 && ft_strncmp(line, "EA", 2) != 0 \
	&& ft_strncmp(line, "F", 1) != 0 && ft_strncmp(line, "C", 1) != 0 \
	&& !ft_stremptyspaces(line))
	{
		return (true);
	}
	return (false);
}

static int	allocate_rows(t_cub *head, char **fcontent, int height)
{
	u_int32_t	lidx;
	int			i;

	lidx = 0;
	while (lidx < head->nb_lines && !is_map_line(fcontent[lidx]))
		lidx++;
	i = 0;
	while (i < height)
	{
		head->map[i] = ft_strdup(fcontent[lidx]);
		if (!head->map[i])
			return (SYSCALL_ERROR);
		i++;
		lidx++;
	}
	return (PARSE_SUCCESS);
}

uint8_t	allocate_map(t_cub *head, char **fcontent, char *map_path)
{
	int	i;

	head->map_height = get_map_height(map_path);
	if (head->map_height < 3)
		return (MWRONG_FORMAT);
	head->map_l_lens = (int *)malloc(sizeof(int) * head->map_height);
	head->map = (char **)ft_calloc(head->map_height + 1, sizeof(char *));
	if (!head->map)
		return (SYSCALL_ERROR);
	if (allocate_rows(head, fcontent, head->map_height))
		return (MWRONG_FORMAT);
	i = 0;
	while (i < head->map_height)
	{
		head->map_l_lens[i] = ft_strlen(head->map[i]);
		i++;
	}
	return (PARSE_SUCCESS);
}
