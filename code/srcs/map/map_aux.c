/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:28:42 by davi              #+#    #+#             */
/*   Updated: 2025/02/11 20:09:08 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_texture_path(char *line)
{
	uint32_t	i;
	uint32_t	size;
	char		*str;

	i = 2;
	str = "";
	size = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[size] == ' ' || line[size] == '\t')
	{
		size--;
	}
	str = ft_substr(line, i, size - i + 1);
	return (str);
}

static void	set_texture(t_cub *head, int8_t orient, char *path)
{
	char	**textures[4];

	textures[0] = &head->assets.no_texture;
	textures[1] = &head->assets.so_texture;
	textures[2] = &head->assets.we_texture;
	textures[3] = &head->assets.ea_texture;
	if (orient >= NO && orient <= EA)
	{
		if (*textures[orient])
			free(path);
		else
			*textures[orient] = path;
	}
}

static void	set_color(t_cub *head, uint8_t orient, char *path)
{
	if (orient == F)
		head->assets.floor_rgb_s = path;
	else if (orient == C)
		head->assets.ceiling_rgb_s = path;
}

static char	*trimspaces(char *str)
{
	uint32_t	i;
	uint32_t	j;
	char		*trimmed;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (ft_isspace(str[i]))
		i++;
	while (j > i && ft_isspace(str[j]))
		j--;
	if (i > j)
		trimmed = ft_substr(str, 0, 0);
	else
		trimmed = ft_substr(str, i, j - i + 1);
	free(str);
	return (trimmed);
}

uint8_t	is_orientation(t_cub *head, int i, int textures_parsed)
{
	if (textures_parsed == 6)
		return (MWRONG_TEXTURE);
	head->fcontent[i] = trimspaces(head->fcontent[i]);
	if (head->fcontent[i] == NULL)
		return (SYSCALL_ERROR);
	if (ft_strncmp(head->fcontent[i], "NO", 2) == 0)
		return (set_texture(head, NO, get_texture_path(head->fcontent[i])), NO);
	else if (ft_strncmp(head->fcontent[i], "SO", 2) == 0)
		return (set_texture(head, SO, get_texture_path(head->fcontent[i])), SO);
	else if (ft_strncmp(head->fcontent[i], "WE", 2) == 0)
		return (set_texture(head, WE, get_texture_path(head->fcontent[i])), WE);
	else if (ft_strncmp(head->fcontent[i], "EA", 2) == 0)
		return (set_texture(head, EA, get_texture_path(head->fcontent[i])), EA);
	else if (ft_strncmp(head->fcontent[i], "F", 1) == 0)
		return (set_color(head, F, get_texture_path(head->fcontent[i])), F);
	else if (ft_strncmp(head->fcontent[i], "C", 1) == 0)
		return (set_color(head, C, get_texture_path(head->fcontent[i])), C);
	else
		return (OTHER);
}
