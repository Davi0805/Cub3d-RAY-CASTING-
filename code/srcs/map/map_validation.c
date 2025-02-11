/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:31 by davi              #+#    #+#             */
/*   Updated: 2025/02/11 20:20:04 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Ends in .cub?
uint8_t	filetype_checker(char *path)
{
	uint32_t	i;

	i = ft_strlen(path);
	if (i <= 4)
		return (FTYPE_ERROR);
	i = i - 4;
	if (ft_strncmp(path + i, ".cub", 4) != 0)
		return (FTYPE_ERROR);
	return (PARSE_SUCCESS);
}

// Verifica se arquivo existe pelo fd retornado
uint8_t	is_file_valid(char *path)
{
	int32_t	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FINVALID_ERROR);
	close(fd);
	return (PARSE_SUCCESS);
}

// Verifica se o arquivo esta vazio
uint8_t	is_file_empty(char *path)
{
	int32_t	fd;
	uint8_t	has_content;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FEMPTY_ERROR);
	if (read(fd, &has_content, 1) == 0)
		return (close(fd), FEMPTY_ERROR);
	close(fd);
	return (PARSE_SUCCESS);
}

// Parser func de RGB
uint8_t	is_color_valid(t_cub *head)
{
	t_rgb	*fcolor;
	t_rgb	*ccolor;

	if (is_color_rgbstring(head->assets.floor_rgb_s) \
		|| is_color_rgbstring(head->assets.ceiling_rgb_s))
		return (MWRONG_TEXTURE);
	fcolor = &(head->assets.floor_color);
	ccolor = &(head->assets.ceil_color);
	fcolor->r = ft_atoi(head->assets.floor_rgb_s);
	fcolor->g = ft_atoi(ft_strchr(head->assets.floor_rgb_s, ',') + 1);
	fcolor->b = ft_atoi(ft_strrchr(head->assets.floor_rgb_s, ',') + 1);
	ccolor->r = ft_atoi(head->assets.ceiling_rgb_s);
	ccolor->g = ft_atoi(ft_strchr(head->assets.ceiling_rgb_s, ',') + 1);
	ccolor->b = ft_atoi(ft_strrchr(head->assets.ceiling_rgb_s, ',') + 1);
	return (PARSE_SUCCESS);
}

// Da parse e valida Texturas e cores
uint8_t	texture_validator(t_cub *head)
{
	uint8_t		i;
	u_int32_t	textures_parsed;

	textures_parsed = 0;
	i = 0;
	while (i < head->nb_lines && textures_parsed != 6)
	{
		errno = 0;
		if (is_orientation(head, i, textures_parsed) != OTHER)
		{
			if (errno != 0)
				return (SYSCALL_ERROR);
			textures_parsed++;
		}
		i++;
	}
	if (textures_parsed != 6)
		return (MWRONG_TEXTURE);
	if (is_texture_valid(head))
		return (MWRONG_TEXTURE);
	if (is_color_valid(head))
		return (MWRONG_TEXTURE);
	return (PARSE_SUCCESS);
}
